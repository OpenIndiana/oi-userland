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
# Copyright 2016 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		node
COMPONENT_FMRI=		runtime/nodejs-6
COMPONENT_SUMMARY=	Evented I/O for V8 JavaScript.
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_PROJECT_URL=	http://nodejs.org
COMPONENT_VERSION=	6.7.0
COMPONENT_LICENSE=	BSD-like, MIT, Apache
COMPONENT_LICENSE_FILE=	node.license	
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:02b8ee1719a11b9ab22bef9279519efaaf31dd0d39cba4c3a1176ccda400b8d6
COMPONENT_ARCHIVE_URL=	http://nodejs.org/dist/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# Include /usr/sbin for dtrace
PATH=/usr/bin:/usr/gnu/bin:/usr/sfw/bin:/usr/ccs/bin:/usr/sbin

CONFIG_SHELL =	$(PYTHON)

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT =	$(@D)/configure

CONFIGURE_OPTIONS= --prefix=/usr/node/6

build:		$(BUILD_32)

install:	$(INSTALL_32)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/math

