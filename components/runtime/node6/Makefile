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
# Copyright 2016, 2017 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		node
COMPONENT_FMRI=		runtime/nodejs-6
COMPONENT_SUMMARY=	Evented I/O for V8 JavaScript.
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_PROJECT_URL=	http://nodejs.org
COMPONENT_VERSION=	6.14.0
COMPONENT_LICENSE=	BSD-like, MIT, Apache
COMPONENT_LICENSE_FILE=	node.license	
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:87892f42c5c48bb6367e0299ec81e1d18e560e401eddc50dd746acc4c896bd7c
COMPONENT_ARCHIVE_URL=	http://nodejs.org/dist/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Include /usr/sbin for dtrace
PATH=$(PATH.gnu)

CONFIG_SHELL =	$(PYTHON)

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT =	$(@D)/configure

CONFIGURE_OPTIONS= --prefix=/usr/node/6

build:		$(BUILD_32)

install:	$(INSTALL_32)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math

