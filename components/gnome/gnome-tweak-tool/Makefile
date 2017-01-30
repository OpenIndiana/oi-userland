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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		NO_ARCH
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-tweak-tool
COMPONENT_VERSION=	3.18.1
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/GnomeTweakTool
COMPONENT_ARCHIVE_HASH= \
	sha256:5c2c1103237648413c2d63a941e06b7057d6b102276b5968517753075de29430
COMPONENT_BUGDB=	gnome/gnome-shell

TPNO=			25847

# No need in S11 since its for Gnome 3
include $(WS_MAKE_RULES)/no-evaluation.mk

PYTHON_VERSIONS= 2.7

include $(WS_MAKE_RULES)/gnome-component.mk

# gtweak/defs.py is accidentally included in the tarball - we remove it so
# that it gets correctly rebuilt from gtweak/defs.py.in with the settings
# passed via the configure script
COMPONENT_POST_UNPACK_ACTION += $(RM) $(SOURCE_DIR)/gtweak/defs.py ;

CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR)

# Assumes GNU msgfmt & xgettext is first in $PATH.
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"

# Ensure Python modules are installed into vendor package directories.
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)

# build .pyc's
COMPONENT_POST_INSTALL_ACTION += $(PYTHON.$(PYTHON_VERSION)) -m compileall \
	$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES) ;

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/env python' so turn it into '#!/usr/bin/python2.7'
PYTHON_SCRIPTS += $(PROTOUSRBINDIR)/gnome-tweak-tool
PYTHON_SCRIPTS += $(PROTOUSRLIBDIR)/gnome-tweak-tool-lid-inhibitor

REQUIRED_PACKAGES += gnome/file-manager/nautilus
REQUIRED_PACKAGES += gnome/gnome-settings-daemon
REQUIRED_PACKAGES += gnome/gnome-shell
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += gnome/window-manager/mutter
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libgweather
REQUIRED_PACKAGES += library/desktop/libnotify
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/gnome/gnome-desktop
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/python/pygobject-3-27
REQUIRED_PACKAGES += runtime/python-27
