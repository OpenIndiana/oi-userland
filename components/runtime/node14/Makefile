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
# Copyright 2020 Andreas Wacknitz <a.wacknitz@gmx.de>
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			node
COMPONENT_MAJOR_VERSION=14
COMPONENT_VERSION=		$(COMPONENT_MAJOR_VERSION).6.0
COMPONENT_FMRI=			runtime/nodejs-$(COMPONENT_MAJOR_VERSION)
COMPONENT_SUMMARY=		Evented I/O for V8 JavaScript.
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_PROJECT_URL=	http://nodejs.org
COMPONENT_LICENSE=		BSD-like, MIT, Apache
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_SRC=			$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:5af300c736088ce8ecabc64ea036ccbf56cf6d072c7374985e7cd7ecdc016a94
COMPONENT_ARCHIVE_URL=	http://nodejs.org/dist/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

TEST_TARGET=			$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION = (cp -a $(SOURCE_DIR)/* $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS= --prefix=/usr/node/$(COMPONENT_MAJOR_VERSION)
CONFIGURE_OPTIONS+= --dest-cpu=x64
CONFIGURE_OPTIONS+= --with-dtrace


# Build dependencies
REQUIRED_PACKAGES += runtime/python-27

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
