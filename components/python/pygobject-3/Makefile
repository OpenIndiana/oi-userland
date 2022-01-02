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
# Copyright 2021 Gary Mills
# Copyright 2017 Alexander Pyhalov
#

BUILD_BITS=		64
BUILD_STYLE=		setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pygobject
# This version only supports python 3.7 - 3.9 inclusive
COMPONENT_VERSION=	3.42.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Python bindings for GObject
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:9b12616e32cfc792f9dc841d9c472a41a35b85ba67d3a6eb427e307a6fe4367b
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/3.42/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/python/pygobject-3
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE_FILE=         COPYING
COMPONENT_LICENSE=      LGPL v2.1

PYTHON_VERSIONS=	3.7 3.9
PYTHON_DATA=		$(USRDIR)

# Tests require gobject-introspection test files, not packaged on OI
TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Rename some files to make way for symlinks
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRINCDIR)/pygobject-3.0; $(MV) pygobject.h pygobject.h-$(PYTHON_VERSION)) ;
COMPONENT_POST_INSTALL_ACTION += \
	(cd $(PROTOUSRLIBDIR)/pkgconfig; $(MKDIR) ../$(MACH64)/pkgconfig; $(MV) pygobject-3.0.pc ../$(MACH64)/pkgconfig/pygobject-3.0.pc-$(PYTHON_VERSION)) ;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
