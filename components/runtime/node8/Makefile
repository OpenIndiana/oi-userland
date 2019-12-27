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
# Copyright 2015 EveryCity Ltd. All rights reserved.
# Copyright 2016 Alexander Pyhalov
# Copyright 2016, 2017, 2019 Andreas Wacknitz
#

BUILD_BITS=     		32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			node
COMPONENT_FMRI=			runtime/nodejs-8
COMPONENT_SUMMARY=		Evented I/O for V8 JavaScript.
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_PROJECT_URL=	http://nodejs.org
COMPONENT_VERSION=		8.17.0
COMPONENT_LICENSE=		BSD-like, MIT, Apache
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:5b0d96db482b273f0324c299ead86ecfbc5d033516e5fc37c92cfccb933ef6ff
COMPONENT_ARCHIVE_URL=	http://nodejs.org/dist/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

TEST_TARGET=            $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Include /usr/sbin for dtrace
PATH=$(PATH.illumos)

CONFIG_SHELL =	$(PYTHON)

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT =	$(@D)/configure

CONFIGURE_OPTIONS= --prefix=/usr/node/8


# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
