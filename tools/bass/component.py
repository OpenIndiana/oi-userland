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
# Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
#
#
# bass-o-matic.py
#  A simple program to enumerate components in the userland gate and report
#  on dependency related information.
#

import os
import subprocess
import json

class Component(object):
    def __init__(self, path=None, debug=False):
        self.debug = debug
        self.path = path
        self.name = None
        self.supplied_packages = []
        self.required_packages = []
        if path:
            component_pkg5_file = os.path.join(self.path, 'pkg5')
            if not os.path.isfile(component_pkg5_file):
                # get component name
                component_name = self.run_make(path, 'print-value-COMPONENT_NAME')
                if not component_name:
                    raise ValueError('Component returns empty name at ' + self.path + '.')
                else:
                    self.name = component_name[0]
                # get supplied packages, this may trigger the creation of a pkg5.fmris file
                self.supplied_packages = self.run_make(path, 'print-package-names')
                # always update fmris if list is overriden
                component_pkg5_fmris_file = os.path.join(self.path, 'pkg5.fmris')
                if os.path.isfile(component_pkg5_fmris_file):
                    with open(component_pkg5_fmris_file, 'r') as f:
                        self.supplied_packages = f.read().splitlines()

                # get dependencies
                self.required_packages = self.run_make(path, 'print-required-packages')

                data = { 'name' : self.name,
                         'fmris': self.supplied_packages,
                         'dependencies' : self.required_packages }
                with open(component_pkg5_file, 'w') as f:
                    f.write(json.dumps(data, sort_keys=True, indent=4))
            else:
                with open(component_pkg5_file, 'r') as f:
                    data = json.loads(f.read())
                if not data:
                    raise ValueError('Component pkg5 data is empty for path ' + self.path + '.')
                self.name = data['name']
                self.supplied_packages = data['fmris']
                self.required_packages = data['dependencies']
            if not self.supplied_packages or not self.supplied_packages[0]:
                raise ValueError('Empty list of supplied FMRIs\npath = ' + self.path)

    def required(self, component):
        result = False

        s1 = set(self.required_packages)
        s2 = set(component.supplied_packages)
        if s1.intersection(s2):
            result = True

        return result

    def run_make(self, path, targets):

        result = []

        if self.debug:
            logger.debug('Executing \'gmake %s\' in %s', targets, path)

        proc = subprocess.Popen(['GNUMAKEFLAGS=--no-print-directory', 'gmake', '-s', targets],
                                stdout=subprocess.PIPE,
                                stderr=subprocess.DEVNULL,
                                cwd=path,
                                universal_newlines=True)
        stdout, stderr = proc.communicate()

        for out in stdout.splitlines():
            result.append(out.rstrip())

        if self.debug:
            if proc.returncode != 0:
                logger.debug('exit: %d, %s', proc.returncode, stderr)

        return result

    def __str__(self):
        result = 'Component:\n\tPath: %s\n' % self.path
        result += '\tProvides Package(s):\n\t\t%s\n' % '\t\t'.join(self.supplied_packages)
        result += '\tRequired Package(s):\n\t\t%s\n' % '\t\t'.join(self.required_packages)

        return result

