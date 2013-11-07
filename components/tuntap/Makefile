#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

# 
# Copyright 2013, Adam Stevko. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tuntap
COMPONENT_VERSION=	1.3.0
COMPONENT_LICENSE=	GPLv2
COMPONENT_GIT_REV=	16eed2b
COMPONENT_SRC=		kaizawa-$(COMPONENT_NAME)-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:25e0cfcdd47ffcd814b40b2e6e89670650c85634b566ed615c789ccacd0eca42
COMPONENT_PROJECT_URL=	http://www.whiteboard.ne.jp/~admin2/tuntap/
COMPONENT_ARCHIVE_URL= 	https://codeload.github.com/kaizawa/tuntap/legacy.tar.gz/$(COMPONENT_GIT_REV)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATCH_LEVEL = 0

CFLAGS +=	$(CPP_LARGEFILES)
LDFLAGS +=	$(LD_Z_DEFS) $(LD_Z_TEXT) -lpthread

CONFIGURE_OPTIONS.32 +=  --disable-64bit
CONFIGURE_OPTIONS.64 +=  --enable-64bit

PKGLINT=true

# common targets
build:          $(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
