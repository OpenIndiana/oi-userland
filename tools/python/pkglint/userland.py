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

#
# Copyright (c) 2010, 2013, Oracle and/or its affiliates. All rights reserved.
#

# Some userland consolidation specific lint checks

import pkg.lint.base as base
from pkg.lint.engine import lint_fmri_successor
import pkg.fmri
import pkg.elf as elf
import re
import os.path
import subprocess
import pkg.client.api
import pkg.client.api_errors
import pkg.client.progress

class UserlandActionChecker(base.ActionChecker):
        """An opensolaris.org-specific class to check actions."""

        name = "userland.action"

        def __init__(self, config):
                self.description = _(
                    "checks Userland packages for common content errors")
                path = os.getenv('PROTO_PATH')
                if path != None:
                        self.proto_path = path.split()
                else:
                        self.proto_path = None
                #
                # These lists are used to check if a 32/64-bit binary
                # is in a proper 32/64-bit directory.
                #
                self.pathlist32 = [
                        "i86",
                        "sparcv7",
                        "32",
                        "i86pc-solaris-64int",  # perl path
                        "sun4-solaris-64int"    # perl path
                ]
                self.pathlist64 = [
                        "amd64",
                        "sparcv9",
                        "64",
                        "i86pc-solaris-64",     # perl path
                        "sun4-solaris-64"       # perl path
                ]
                self.runpath_re = [
                        re.compile('^/lib(/.*)?$'),
                        re.compile('^/usr/'),
                        re.compile('^\$ORIGIN/')
                ]
                self.runpath_64_re = [
                        re.compile('^.*/64(/.*)?$'),
                        re.compile('^.*/amd64(/.*)?$'),
                        re.compile('^.*/sparcv9(/.*)?$'),
                        re.compile('^.*/i86pc-solaris-64(/.*)?$'), # perl path
                        re.compile('^.*/sun4-solaris-64(/.*)?$')   # perl path
                ]
                self.initscript_re = re.compile("^etc/(rc.|init)\.d")

                self.lint_paths = {}
                self.ref_paths = {}

                super(UserlandActionChecker, self).__init__(config)

        def startup(self, engine):
                """Initialize the checker with a dictionary of paths, so that we
                can do link resolution.

                This is copied from the core pkglint code, but should eventually
                be made common.
                """

                def seed_dict(mf, attr, dic, atype=None, verbose=False):
                        """Updates a dictionary of { attr: [(fmri, action), ..]}
                        where attr is the value of that attribute from
                        actions of a given type atype, in the given
                        manifest."""

                        pkg_vars = mf.get_all_variants()

                        if atype:
                                mfg = (a for a in mf.gen_actions_by_type(atype))
                        else:
                                mfg = (a for a in mf.gen_actions())

                        for action in mfg:
                                if atype and action.name != atype:
                                        continue
                                if attr not in action.attrs:
                                        continue

                                variants = action.get_variant_template()
                                variants.merge_unknown(pkg_vars)
                                action.attrs.update(variants)

                                p = action.attrs[attr]
                                dic.setdefault(p, []).append((mf.fmri, action))

                # construct a set of FMRIs being presented for linting, and
                # avoid seeding the reference dictionary with any for which
                # we're delivering new packages.
                lint_fmris = {}
                for m in engine.gen_manifests(engine.lint_api_inst,
                    release=engine.release, pattern=engine.pattern):
                        lint_fmris.setdefault(m.fmri.get_name(), []).append(m.fmri)
                for m in engine.lint_manifests:
                        lint_fmris.setdefault(m.fmri.get_name(), []).append(m.fmri)

                engine.logger.debug(
                    _("Seeding reference action path dictionaries."))

                for manifest in engine.gen_manifests(engine.ref_api_inst,
                    release=engine.release):
                        # Only put this manifest into the reference dictionary
                        # if it's not an older version of the same package.
                        if not any(
                            lint_fmri_successor(fmri, manifest.fmri)
                            for fmri
                            in lint_fmris.get(manifest.fmri.get_name(), [])
                        ):
                                seed_dict(manifest, "path", self.ref_paths)

                engine.logger.debug(
                    _("Seeding lint action path dictionaries."))

                # we provide a search pattern, to allow users to lint a
                # subset of the packages in the lint_repository
                for manifest in engine.gen_manifests(engine.lint_api_inst,
                    release=engine.release, pattern=engine.pattern):
                        seed_dict(manifest, "path", self.lint_paths)

                engine.logger.debug(
                    _("Seeding local action path dictionaries."))

                for manifest in engine.lint_manifests:
                        seed_dict(manifest, "path", self.lint_paths)

                self.__merge_dict(self.lint_paths, self.ref_paths,
                    ignore_pubs=engine.ignore_pubs)

        def __merge_dict(self, src, target, ignore_pubs=True):
                """Merges the given src dictionary into the target
                dictionary, giving us the target content as it would appear,
                were the packages in src to get published to the
                repositories that made up target.

                We need to only merge packages at the same or successive
                version from the src dictionary into the target dictionary.
                If the src dictionary contains a package with no version
                information, it is assumed to be more recent than the same
                package with no version in the target."""

                for p in src:
                        if p not in target:
                                target[p] = src[p]
                                continue

                        def build_dic(arr):
                                """Builds a dictionary of fmri:action entries"""
                                dic = {}
                                for (pfmri, action) in arr:
                                        if pfmri in dic:
                                                dic[pfmri].append(action)
                                        else:
                                                dic[pfmri] = [action]
                                return dic

                        src_dic = build_dic(src[p])
                        targ_dic = build_dic(target[p])

                        for src_pfmri in src_dic:
                                # we want to remove entries deemed older than
                                # src_pfmri from targ_dic.
                                for targ_pfmri in targ_dic.copy():
                                        sname = src_pfmri.get_name()
                                        tname = targ_pfmri.get_name()
                                        if lint_fmri_successor(src_pfmri,
                                            targ_pfmri,
                                            ignore_pubs=ignore_pubs):
                                                targ_dic.pop(targ_pfmri)
                        targ_dic.update(src_dic)
                        l = []
                        for pfmri in targ_dic:
                                for action in targ_dic[pfmri]:
                                        l.append((pfmri, action))
                        target[p] = l

        def __realpath(self, path, target):
                """Combine path and target to get the real path."""

                result = os.path.dirname(path)

                for frag in target.split(os.sep):
                        if frag == '..':
                                result = os.path.dirname(result)
                        elif frag == '.':
                                pass
                        else:
                                result = os.path.join(result, frag)

                return result

        def __elf_aslr_check(self, path, engine):
                result = None

                ei = elf.get_info(path)
                type = ei.get("type");
                if type != "exe":
                        return result

                # get the ASLR tag string for this binary
                aslr_tag_process = subprocess.Popen(
                        "/usr/bin/elfedit -r -e 'dyn:sunw_aslr' "
                        + path, shell=True,
                        stdout=subprocess.PIPE, stderr=subprocess.PIPE)

                # aslr_tag_string will get stdout; err will get stderr
                aslr_tag_string, err = aslr_tag_process.communicate()

                # No ASLR tag was found; everthing must be tagged
                if aslr_tag_process.returncode != 0:
                        engine.error(
                                _("'%s' is not tagged for aslr") % (path),
                                msgid="%s%s.5" % (self.name, "001"))
                        return result

                # look for "ENABLE" anywhere in the string;
                # warn about binaries which are not ASLR enabled
                if re.search("ENABLE", aslr_tag_string) is not None:
                        return result
                engine.warning(
                        _("'%s' does not have aslr enabled") % (path),
                        msgid="%s%s.6" % (self.name, "001"))
                return result

        def __elf_runpath_check(self, path, engine):
                result = None
                list = []

                ed = elf.get_dynamic(path)
                ei = elf.get_info(path)
                bits = ei.get("bits")
                for dir in ed.get("runpath", "").split(":"):
                        if dir == None or dir == '':
                                continue

                        match = False
                        for expr in self.runpath_re:
                                if expr.match(dir):
                                        match = True
                                        break

                        # The RUNPATH shouldn't contain any runtime linker
                        # default paths (or the /64 equivalent link)
                        if dir in ['/lib', '/lib/64',
                                   '/lib/amd64', '/lib/sparcv9',
                                   '/usr/lib', '/usr/lib/64',
                                   '/usr/lib/amd64', '/usr/lib/sparcv9' ]:
                                list.append(dir)

                        if match == False:
                                list.append(dir)

                        if bits == 32:
                                for expr in self.runpath_64_re:
                                        if expr.search(dir):
                                                engine.warning(
                                                        _("64-bit runpath in 32-bit binary, '%s' includes '%s'") % (path, dir),
                                                        msgid="%s%s.3" % (self.name, "001"))
                        else:
                                match = False
                                for expr in self.runpath_64_re:
                                        if expr.search(dir):
                                                match = True
                                                break
                                if match == False:
                                        engine.warning(
                                                _("32-bit runpath in 64-bit binary, '%s' includes '%s'") % (path, dir),
                                                msgid="%s%s.3" % (self.name, "001"))
                if len(list) > 0:
                        result = _("bad RUNPATH, '%%s' includes '%s'" %
                                   ":".join(list))

                return result

        def __elf_wrong_location_check(self, path):
                result = None

                ei = elf.get_info(path)
                bits = ei.get("bits")
                type = ei.get("type");
                elems = os.path.dirname(path).split("/")

                path64 = False
                for p in self.pathlist64:
                    if (p in elems):
                            path64 = True

                path32 = False
                for p in self.pathlist32:
                    if (p in elems):
                            path32 = True

                # ignore 64-bit executables in normal (non-32-bit-specific)
                # locations, that's ok now.
                if (type == "exe" and bits == 64 and path32 == False and path64 == False):
                        return result

                if bits == 32 and path64:
                        result = _("32-bit object '%s' in 64-bit path")
                elif bits == 64 and not path64:
                        result = _("64-bit object '%s' in 32-bit path")
                return result

        def file_action(self, action, manifest, engine, pkglint_id="001"):
                """Checks for existence in the proto area."""

                if action.name not in ["file"]:
                        return

                path = action.hash
                if path == None or path == 'NOHASH':
                        path = action.attrs["path"]

                # check for writable files without a preserve attribute
                if "mode" in action.attrs:
                        mode = action.attrs["mode"]

                        if (int(mode, 8) & 0o222) != 0 and "preserve" not in action.attrs:
                                engine.error(
                                _("%(path)s is writable (%(mode)s), but missing a preserve"
                                  " attribute") %  {"path": path, "mode": mode},
                                msgid="%s%s.0" % (self.name, pkglint_id))
                elif "preserve" in action.attrs:
                        if "mode" in action.attrs:
                                mode = action.attrs["mode"]
                                if (int(mode, 8) & 0o222) == 0:
                                        engine.error(
                                        _("%(path)s has a preserve action, but is not writable (%(mode)s)") %  {"path": path, "mode": mode},
                                msgid="%s%s.4" % (self.name, pkglint_id))
                        else:
                                engine.error(
                                _("%(path)s has a preserve action, but no mode") %  {"path": path, "mode": mode},
                                msgid="%s%s.3" % (self.name, pkglint_id))

                # checks that require a physical file to look at
                if self.proto_path is not None:
                        for directory in self.proto_path:
                                fullpath = directory + "/" + path

                                if os.path.exists(fullpath):
                                        break

                        if not os.path.exists(fullpath):
                                engine.info(
                                        _("%s missing from proto area, skipping"
                                          " content checks") % path, 
                                        msgid="%s%s.1" % (self.name, pkglint_id))
                        elif elf.is_elf_object(fullpath):
                                # 32/64 bit in wrong place
                                result = self.__elf_wrong_location_check(fullpath)
                                if result != None:
                                        engine.error(result % path, 
                                                msgid="%s%s.2" % (self.name, pkglint_id))
                                result = self.__elf_runpath_check(fullpath, engine)
                                if result != None:
                                        engine.error(result % path, 
                                                msgid="%s%s.3" % (self.name, pkglint_id))
                                # illumos does not support ASLR
                                #result = self.__elf_aslr_check(fullpath, engine)

        file_action.pkglint_desc = _("Paths should exist in the proto area.")

        def link_resolves(self, action, manifest, engine, pkglint_id="002"):
                """Checks for link resolution."""

                if action.name not in ["link", "hardlink"]:
                        return

                path = action.attrs["path"]
                target = action.attrs["target"]
                realtarget = self.__realpath(path, target)

                # Check against the target image (ref_paths), since links might
                # resolve outside the packages delivering a particular
                # component.

                # links to files should directly match a patch in the reference
                # repo.
                if self.ref_paths.get(realtarget, None):
                        return

                # If it didn't match a path in the reference repo, it may still
                # be a link to a directory that has no action because it uses
                # the default attributes.  Look for a path that starts with
                # this value plus a trailing slash to be sure this it will be
                # resolvable on a fully installed system.
                realtarget += '/'
                for key in self.ref_paths:
                        if key.startswith(realtarget):
                                return

                engine.error(_("%s %s has unresolvable target '%s'") %
                                (action.name, path, target),
                        msgid="%s%s.0" % (self.name, pkglint_id))

        link_resolves.pkglint_desc = _("links should resolve.")

        def init_script(self, action, manifest, engine, pkglint_id="003"):
                """Checks for SVR4 startup scripts."""

                if action.name not in ["file", "dir", "link", "hardlink"]:
                        return

                path = action.attrs["path"]
                if self.initscript_re.match(path):
                        engine.warning(
                                _("SVR4 startup '%s', deliver SMF"
                                  " service instead") % path,
                                msgid="%s%s.0" % (self.name, pkglint_id))

        init_script.pkglint_desc = _(
                "SVR4 startup scripts should not be delivered.")

class UserlandManifestChecker(base.ManifestChecker):
        """An opensolaris.org-specific class to check manifests."""

        name = "userland.manifest"

        def __init__(self, config):
                super(UserlandManifestChecker, self).__init__(config)

        def forbidden_publisher(self, manifest, engine, pkglint_id="1001"):
                if not os.environ.get("ENCUMBERED"):
                        for action in manifest.gen_actions_by_type("depend"):
                                for f in action.attrlist("fmri"):
                                        pkg_name=pkg.fmri.PkgFmri(f).pkg_name
                                        info_needed = pkg.client.api.PackageInfo.ALL_OPTIONS - \
                                            (pkg.client.api.PackageInfo.ACTION_OPTIONS |
                                             frozenset([pkg.client.api.PackageInfo.LICENSES]))
                                        progtracker = pkg.client.progress.NullProgressTracker()
                                        interface=pkg.client.api.ImageInterface("/", pkg.client.api.CURRENT_API_VERSION, progtracker, lambda x: False, None,None)
                                        ret = interface.info([pkg_name],True,info_needed)
                                        if ret[pkg.client.api.ImageInterface.INFO_FOUND]:
                                                allowed_pubs = engine.get_param("%s.allowed_pubs" % self.name).split(" ") + ["openindiana.org","on-nightly"]
                                                for i in ret[pkg.client.api.ImageInterface.INFO_FOUND]:
                                                        if i.publisher not in allowed_pubs:
                                                                engine.error(_("package %(pkg)s depends on %(name)s, which comes from forbidden publisher %(publisher)s") %
                                                                        {"pkg":manifest.fmri,"name":pkg_name,"publisher":i.publisher}, msgid="%s%s.1" % (self.name, pkglint_id))

        forbidden_publisher.pkglint_desc = _(
                "Dependencies should come from standard publishers" )

        def component_check(self, manifest, engine, pkglint_id="001"):
                manifest_paths = []
                files = False
                license = False

                for action in manifest.gen_actions_by_type("file"):
                        files = True
                        break

                if files == False:
                        return

                for action in manifest.gen_actions_by_type("license"):
                        if not action.attrs['license']:
                                engine.error( _("missing vaue for action license attribute 'license' like 'CDDL','MIT','GPL'..."),
                                    msgid="%s%s.0" % (self.name, pkglint_id))
                        else:
                                license = True
                                break

                if license == False:
                        engine.error( _("missing license action"),
                                msgid="%s%s.0" % (self.name, pkglint_id))

#                if 'org.opensolaris.arc-caseid' not in manifest:
#                        engine.error( _("missing ARC data (org.opensolaris.arc-caseid)"),
#                                msgid="%s%s.0" % (self.name, pkglint_id))

        component_check.pkglint_desc = _(
                "license actions and ARC information are required if you deliver files.")

        def publisher_in_fmri(self, manifest, engine, pkglint_id="002"):
                allowed_pubs = engine.get_param(
                    "%s.allowed_pubs" % self.name).split(" ")

                fmri = manifest.fmri
                if fmri.publisher and fmri.publisher not in allowed_pubs:
                        engine.error(_("package %s has a publisher set!") %
                            manifest.fmri,
                            msgid="%s%s.2" % (self.name, pkglint_id))

        publisher_in_fmri.pkglint_desc = _(
                "extra publisher set" )
