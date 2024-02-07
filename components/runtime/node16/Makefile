#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2021 Andreas Wacknitz <a.wacknitz@gmx.de>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			node
COMPONENT_MAJOR_VERSION=16
COMPONENT_VERSION=		$(COMPONENT_MAJOR_VERSION).20.2
COMPONENT_SUMMARY=		Evented I/O for V8 JavaScript
COMPONENT_PROJECT_URL=	https://nodejs.org
COMPONENT_SRC=			$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:576f1a03c455e491a8d132b587eb6b3b84651fc8974bb3638433dd44d22c8f49
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/dist/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			runtime/nodejs-$(COMPONENT_MAJOR_VERSION)
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=		BSD-like, MIT, Apache
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION = ( cp -a $(SOURCE_DIR)/* $(@D) )

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS  = --prefix=/usr/node/$(COMPONENT_MAJOR_VERSION)
CONFIGURE_OPTIONS += --dest-cpu=x64
CONFIGURE_OPTIONS += --with-dtrace

# Manually added build-dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
