#!/usr/bin/python
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
# Copyright (c) 2010, 2011, Oracle and/or its affiliates. All rights reserved.
#

# Some userland consolidation specific lint checks

import pkg.lint.base as base
import pkg.elf as elf
import re
import os.path


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
		self.runpath_re = [
			re.compile('^/lib(/.*)?$'),
			re.compile('^/usr/'),
			re.compile('^\$ORIGIN/')
		]
		self.initscript_re = re.compile("^etc/(rc.|init)\.d")
                super(UserlandActionChecker, self).__init__(config)

	def startup(self, engine):
		pass

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

	def __elf_runpath_check(self, path):
		result = None
		list = []

		ed = elf.get_dynamic(path)
		for dir in ed.get("runpath", "").split(":"):
			if dir == None or dir == '':
				continue

			match = False
			for expr in self.runpath_re:
				if expr.match(dir):
					match = True
					break

			if match == False:
				list.append(dir)

		if len(list) > 0:
			result = _("bad RUNPATH, '%%s' includes '%s'" %
				   ":".join(list))

		return result

	def __elf_wrong_location_check(self, path):
		result = None

		ei = elf.get_info(path)
		bits = ei.get("bits")
		frag = os.path.basename(os.path.dirname(path))

		if bits == 32 and frag in ["sparcv9", "amd64", "64"]:
			result = _("32-bit object '%s' in 64-bit path")
		elif bits == 64 and frag not in ["sparcv9", "amd64", "64"]:
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
		if 'mode' in action.attrs:
			mode = action.attrs["mode"]

			if (int(mode, 8) & 0222) != 0 and "preserve" not in action.attrs:
				engine.error(
				_("%(path)s is writable (%(mode)s), but missing a preserve"
				  " attribute") %  {"path": path, "mode": mode},
				msgid="%s%s.0" % (self.name, pkglint_id))

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
				result = self.__elf_runpath_check(fullpath)
				if result != None:
					engine.error(result % path, 
						msgid="%s%s.3" % (self.name, pkglint_id))

	file_action.pkglint_desc = _("Paths should exist in the proto area.")

	def link_resolves(self, action, manifest, engine, pkglint_id="002"):
		"""Checks for link resolution."""

		if action.name not in ["link", "hardlink"]:
			return

		path = action.attrs["path"]
		target = action.attrs["target"]
		realtarget = self.__realpath(path, target)
		
		resolved = False
		for maction in manifest.gen_actions():
			mpath = None
			if maction.name in ["dir", "file", "link",
						"hardlink"]:
				mpath = maction.attrs["path"]

			if mpath and mpath == realtarget:
				resolved = True
				break

		if resolved != True:
			engine.error(
				_("%s %s has unresolvable target '%s'") %
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

	def license_check(self, manifest, engine, pkglint_id="001"):
		manifest_paths = []
		files = False
		license = False

		for action in manifest.gen_actions_by_type("file"):
			files = True
			break

		if files == False:
			return

		for action in manifest.gen_actions_by_type("license"):
			return

		engine.error( _("missing license action"),
			msgid="%s%s.0" % (self.name, pkglint_id))

	license_check.pkglint_dest = _(
		"license actions are required if you deliver files.")
