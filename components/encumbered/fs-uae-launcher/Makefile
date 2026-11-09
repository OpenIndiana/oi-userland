#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2026 Ignacio Soriano
#

# FS-UAE Launcher is a standalone Python application (PyQt5), not a module:
# upstream installs it into $(prefix)/share/fs-uae-launcher (setup.py refuses
# the default site-packages) and links $(prefix)/bin/fs-uae-launcher to it.
# Its own Makefile does that, so this uses justmake: "mo" builds the message
# catalogs, "install" runs setup.py.
BUILD_BITS =		NO_ARCH
BUILD_STYLE =		justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =	fs-uae-launcher
COMPONENT_VERSION =	3.2.35
COMPONENT_SUMMARY =	FS-UAE Launcher, the graphical front end of FS-UAE
COMPONENT_PROJECT_URL =	https://fs-uae.net/
COMPONENT_FMRI =	emulators/fs-uae-launcher
COMPONENT_CLASSIFICATION = Applications/System Utilities
COMPONENT_SRC =		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL =	https://github.com/FrodeSolheim/fs-uae-launcher/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH = sha256:cdfd74cd99281931a904340d414c7ebc44ddbdd0d0d599b3eb9818d58105dc25
COMPONENT_LICENSE =	GPLv2
COMPONENT_LICENSE_FILE = fs-uae-launcher.license

TEST_TARGET =		$(NO_TESTS)

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

PATH =			$(PATH.gnu)

# A real copy of the source tree, not a symlink farm: upstream's
# install-data does "cp -a share/*", which would deliver the symlinks.
CLONEY_MODE =		copy

COMPONENT_BUILD_TARGETS = mo
COMPONENT_INSTALL_TARGETS = install
COMPONENT_INSTALL_ARGS += prefix=$(USRDIR)

# setup.py writes "#!/usr/bin/python3" into the launcher script.  pkgdepend
# refuses an executable Python script without a version, and PyQt5 exists
# for Python 3.9 only, so pin it to the interpreter the package needs.
COMPONENT_POST_INSTALL_ACTION += \
	$(GSED) -i '1s|^\#!/usr/bin/python3$$|\#!/usr/bin/python3.9|' \
		$(PROTO_DIR)$(USRSHAREDIR)/fs-uae-launcher/fs-uae-launcher

# PyOpenGL, PyQt5 and requests are needed at run time only; the manifest
# names them.
REQUIRED_PACKAGES += library/python/pyqt5-39
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += text/gnu-gettext
