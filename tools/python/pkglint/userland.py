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
# Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved.
#

# Some userland consolidation specific lint checks

import pkg.lint.base as base
import re
import os.path

class UserlandActionChecker(base.ActionChecker):
        """An opensolaris.org-specific class to check actions."""

        name = "userland.action"

        def __init__(self, config):
                self.description = _(
                    "checks Userland packages for common content errors")
		self.prototype = os.getenv('PROTO_DIR')
		self.runpath_re = [
			re.compile('^/lib/'),
			re.compile('^/usr/'),
			re.compile('^\$ORIGIN/')
		]
                super(UserlandActionChecker, self).__init__(config)

	def startup(self, engine):
		if self.prototype != None:
			engine.info(_("including prototype checks: %s") % self.prototype, msgid=self.name)

	def file_exists(self, action, manifest, engine, pkglint_id="001"):
		"""Checks for existence in the proto area."""

		if self.prototype is None:
			return

		if action.name not in ["file", "dir", "link", "hardlink"]:
			return

		path = action.attrs["path"]
		fullpath = self.prototype + "/" + path
		if not os.path.exists(fullpath):
			engine.error(
				_("packaged path '%s' missing from proto area") % path, 
				msgid="%s%s.0" % (self.name, pkglint_id))

	file_exists.pkglint_desc = _("Paths should exist in the proto area.")

	def file_content(self, action, manifest, engine, pkglint_id="002"):
		"""Checks for file content issues."""

		if self.prototype is None:
			return

		if action.name is not "file":
			return

		import pkg.elf as elf

		path = action.attrs["path"]
		fullpath = self.prototype + "/" + path

		if elf.is_elf_object(fullpath):
			ed = elf.get_dynamic(fullpath)
			for dir in ed.get("runpath", "").split(":"):
				if dir == None or dir == '':
					continue

				match = False
				for expr in self.runpath_re:
					if expr.match(dir):
						match = True
						break

				if match == False:
					engine.error(
						_("%s has bad RUNPATH, "
					  	"includes: %s") % (path, dir),
						msgid="%s%s.1" % (self.name, pkglint_id))
		# additional checks for different content types should go here

	file_content.pkglint_desc = _("Paths should not deliver common mistakes.")

class UserlandManifestChecker(base.ManifestChecker):
        """An opensolaris.org-specific class to check manifests."""

        name = "userland.manifest"

	def __init__(self, config):
		self.prototype = os.getenv('PROTO_DIR')
		super(UserlandManifestChecker, self).__init__(config)

	def unpackaged_files(self, manifest, engine, pkglint_id="001"):
		if self.prototype == None:
			return

		return	# skip this check for now.  It needs more work

		manifest_paths = []

		for action in manifest.gen_actions():
			if action.name in ["file", "dir", "link", "hardlink"]:
				manifest_paths.append(action.attrs.get("path"))

		for dirname, dirnames, filenames in os.walk(self.prototype):
			dir = dirname[len(self.prototype):]
			for name in filenames + dirnames:
				path = dir + '/' + name
				if path not in manifest_paths:
					engine.error(
						_("unpackaged path '%s' missing from manifest") % path, 
					msgid="%s%s.0" % (self.name, pkglint_id))

	unpackaged_files.pkglint_dest = _(
		"Prototype paths should be present.")

