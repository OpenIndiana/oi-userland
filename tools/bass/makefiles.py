#!/usr/bin/python3.5
#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# This is all very naive and will hurt pythonists' eyes.
#

import json
import os
import re
import subprocess
import warnings
from urllib.request import urlopen

from .component import Component


class Keywords(object):
    def __init__(self):
        self.variables = {
            "BUILD_BITS":
            ["NO_ARCH",
             "32",
             "64",
             "32_and_64",
             "64_and_32"],
            "BUILD_STYLE":
                ["ant",
                 "attpackagemake",
                 "cmake",
                 "configure",
                 "gem",
                 "justmake",
                 "makemaker",
                 "meson",
                 "ocaml",
                 "setup.py",
                 "waf"],
            "MK_BITS":
            ["NO_ARCH",
             "32",
             "64",
             "32_and_64"],
            "COMPONENT_NAME": [],
            "COMPONENT_VERSION": [],
            "COMPONENT_REVISION": [],
            "COMPONENT_FMRI": [],
            "COMPONENT_CLASSIFICATION": [],
            "COMPONENT_SUMMARY": [],
            "COMPONENT_PROJECT_URL": [],
            "COMPONENT_SRC": ["$(COMPONENT_NAME)-$(COMPONENT_VERSION)"],
            "COMPONENT_ARCHIVE": [],
            "COMPONENT_ARCHIVE_URL": [],
            "COMPONENT_ARCHIVE_HASH": [],
            "COMPONENT_LICENSE": [],
            "COMPONENT_LICENSE_FILE": []
        }
        self.targets = {
            "build": [ "BUILD_$(MK_BITS)"],
            "install": ["INSTALL_$(MK_BITS)"],
            "test": ["TEST_$(MK_BITS)", "NO_TESTS"],
            "system-test": ["SYSTEM_TEST_$(MK_BITS)", "SYSTEM_TESTS_NOT_IMPLEMENTED"]
        }

    @staticmethod
    def assignment(name, value):
        return name + "=" + value + "\n"

    @staticmethod
    def target_variable_assignment(name, value):
        return Keywords.assignment(name.upper()+"_TARGET", value)


class Item(object):
    def __init__(self, line=None, content=[]):
        self.idx = line 
        self.str = content
        for l in iter(self.str):
            l = l.strip() 

    def append(self, line):
        self.str.append(line.strip())

    def extend(self, content):
        for l in content:
            self.append(l)

    def line(self):
        return self.idx

    def length(self):
        return len(self.str)

    def value(self):
        return "".join(self.str).replace("\n","").strip()

    def set_value(self, value):
        self.str = [ i.strip()+"\n" for i in value.split("\n") ]

    def include_line(self):
        return "include "+self.str[0]

    def variable_assignment(self, variable):
        if self.length() == 1:
            return ["{0:<24}{1}".format(variable+"=",self.str[0])]
        # Handle continuation lines
        lines = ["{0:<24}{1}".format(variable+"=",self.str[0])]
        for l in self.str[1:]:
            lines[-1] += "\\\n"
            lines.append("\t"+l)
        lines[-1] += "\n"
        return lines

    def target_definition(self, target):
        lines = ["{0:<24}{1}".format(target+":", self.str[0])]
        for l in self.str[1:]:
            lines.append("\t"+l)
        return lines


class Makefile(object):
    def __init__(self, path=None, debug=False):
        self.debug = debug
        self.path = path
        self.component = Component()
        self.includes = []
        self.variables = {}
        self.targets = {}
        makefile = os.path.join(path, 'Makefile')
        with open(makefile, 'r') as f:
            self.contents = f.readlines()
        self.update()

    def update(self, contents=None):
        self.includes = []
        self.variables = {}
        self.targets = {}
        if contents is not None:
            self.contents = contents
        # Construct list of keywords
        kw = Keywords()

        # Variable is set
        m = None
        # Target is set
        t = None
        # Rule definition
        d = None
        for idx, line in enumerate(self.contents):
            # Continuation of target line
            if t is not None:
                r = re.match(r"^[\s]*(.*)[\s]*([\\]?)[\s]*$", line)
                # Concatenate
                self.targets[t].str[0] += "\\".join(r.group(1))
                # Check for continuation or move to definition
                if not r.group(2):
                    d = t 
                    t = None
                continue
            if d is not None:
                # Concatenate
                r = re.match(r"^[\t][\s]*(.*)[\s]*$", line)
                # End of definition
                if r is None:
                    d = None
                    continue
                self.targets[d].append(r.group(1))
            # Continuation line of variable
            if m is not None:
                r = re.match(r"^[\s]*(.*)[\s]*([\\]?)[\s]*$", line)
                self.variables[m].append(r.group(1))
                if not r.group(2):
                    m = None
                continue
            if re.match(r"^#", line):
                continue
            # Check for include
            r = re.match(r"^include[\s]+(.*)", line)
            if r is not None:
               self.includes.append(Item(idx, [r.group(1)]))
            else:
                found = False
                # Collect known variables
                for k in list(kw.variables.keys()):
                    r = re.match(
                        r"^[\s]*("+k+r")[\s]*=[\s]*([^\\]*)[\s]*([\\]?)[\s]*$", line)
                    if r is not None:
                        found = True
                        v = r.group(2)
                        if v in self.variables.keys():
                            warnings.warn("Variable '"+v+"' redefined line "+idx)
                        self.variables[k] = Item(idx, [v])
                        if r.group(3):
                            m = k
                        break
                if found is True:
                    continue
                # Collect known targets
                for k in list(kw.targets.keys()):
                    r = re.match(
                        "^"+k+r"[\s]*:[\s]*(.*)[\s]*([\\]?)[\s]*$", line)
                    if r is not None:
                        found = True
                        v = r.group(1)
                        if v in self.targets.keys():
                            warnings.warn("Target '"+v+"' redefined line "+idx)
                        self.targets[k] = Item(idx, [v])
                        if r.group(2):
                            t = k
                            d = None
                        else:
                            t = None
                            d = k
                        break
                if found is True:
                    continue

    def write(self):
        with open(os.path.join(self.path, "Makefile"), 'w') as f:
            for line in self.contents:
                f.write(line)

    def display(self):
        print(self.path)
        print('-' * 78)
        if self.includes:
            print("includes:")
            print("---------")
            for i in iter(self.includes):
                print("{0:>3}: {1}".format(i.line(), i.value()))
            print("")
        if self.variables:
            print("variables:")
            print("----------")
            for k,i in iter(sorted(self.variables.items())):
                print("{0:>3}: {1:<24}= {2}".format(i.line(), k, i.value()))
            print("")
        if self.targets:
            print("targets:")
            print("--------")
            for k,i in iter(sorted(self.targets.items())):
                print("{0:>3}: {1:<24}= {2}".format(i.line(), k, i.value()))
            print("")
        print('-' * 78)

    def run(self, targets):
        path = self.path
        result = []

        if self.debug:
            logger.debug('Executing \'gmake %s\' in %s', targets, path)

        proc = subprocess.Popen(['gmake', '-s', targets],
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE,
                                cwd=path,
                                universal_newlines=True)
        stdout, stderr = proc.communicate()

        for out in stdout.splitlines():
            result.append(out.rstrip())

        if self.debug:
            if proc.returncode != 0:
                logger.debug('exit: %d, %s', proc.returncode, stderr)

        return result

    def print_value(self, name):
        return self.run('print-value-'+name)[0]

    def build_style(self):
        return self.variables['BUILD_STYLE'].value()

    def build_bits(self):
        return self.variables['BUILD_BITS'].value()

    def has_mk_include(self, name):
        for i in iter(self.includes):
            if re.match('^.*/'+name+'.mk$', i.value()):
                return True
        return False

    def get_mk_include(self, name):
        for i in iter(self.includes):
            if re.match('^.*/'+name+'.mk$', i.value()):
                return i
        return None

    def has_variable(self, variable):
        return variable in self.variables

    def variable(self, variable):
        return self.variables[variable]

    def remove_variable(self, variable):
        idx = self.variable(variable).line()
        del self.contents[idx] 
        self.update()

    def set_variable(self, variable, value, line=None):
        if not self.has_variable(variable):
            self.variables[variable] = Item(None)
            self.variables[variable].set_value(str(value))
            if line is not None:
                contents = self.contents[0:line]
                contents.extend(self.variable_assignment(variable))
                contents.extend(self.contents[line:])
                self.update(contents)
            return True
        else:
            idx = self.variables[variable].line()
            oln = self.variables[variable].length()
            self.variables[variable].set_value(str(value))
            nln = self.variables[variable].length()
            if idx is not None:
                if line is None:
                    line = idx
                if line == idx and nln == 1 and oln == 1: 
                    self.contents[idx] = self.variable_assignment(variable)[0]
                elif line <= idx:
                    contents = self.contents[0:line]
                    contents.extend(self.variable_assignment(variable))
                    contents.extend(self.contents[line:idx])
                    contents.extend(self.contents[idx+oln:])
                    self.update(contents)
                else:
                    contents = self.contents[0:idx]
                    contents.extend(self.contents[idx+oln:line])
                    contents.extend(self.variable_assignment(variable))
                    contents.extend(self.contents[line:])
                    self.update(contents)
            # Add variable at given line
            elif line is not None:
                contents = self.contents[0:line]
                contents.extend(self.variable_assignment(variable))
                contents.extend(self.contents[line:])
                self.update(contents)

    def set_archive_hash(self, checksum):
        self.set_variable('COMPONENT_ARCHIVE_HASH', "sha256:"+str(checksum))

    def variable_assignment(self, variable):
        return self.variables[variable].variable_assignment(variable)

    def has_target(self, target):
        return target in self.targets

    def target(self, target):
        return self.targets[target]

    def target_definition(self, target):
        return self.targets[target].target_definition(target)

    def required_packages(self):
        return self.run("print-value-REQUIRED_PACKAGES")[0]

    def uses_pypi(self):
        # Default build style is configure
        if not self.has_variable('BUILD_STYLE'):
            return False
        is_py = (self.build_style() == 'setup.py')
        urlnone = (not self.has_variable('COMPONENT_ARCHIVE_URL'))
        urlpipy = urlnone or (self.variable('COMPONENT_ARCHIVE_URL').value() == '$(call pypi_url)')
        return is_py and urlpipy

    def get_pypi_data(self):
        name = self.print_value('COMPONENT_PYPI')
        jsurl = "https://pypi.python.org/pypi/%s/json" % name
        try:
            f = urlopen(jsurl, data=None)
        except HTTPError as e:
            if e.getcode() == 404:
                print("Unknown component '%s'" % name)
            else:
                printIOError(e, "Can't open PyPI JSON url %s" % jsurl)
            return None
        except IOError as e:
            printIOError(e, "Can't open PyPI JSON url %s" % jsurl)
            return None
        content = f.read().decode("utf-8")
        return json.loads(content)

    @staticmethod
    def value(variable):
        return "$("+variable+")"

    @staticmethod
    def directory_variable(subdir):
        return Makefile.value("WS_"+subdir.upper().replace("-","_"))

    @staticmethod
    def makefile_path(name):
        return os.path.join("$(WS_MAKE_RULES)", name+".mk")

    @staticmethod
    def target_value(name, bits):
        return Makefile.value(name.upper()+"_"+bits)

