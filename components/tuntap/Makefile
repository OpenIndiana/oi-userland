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
# Copyright 2013, Adam Stevko. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tuntap
COMPONENT_VERSION=	1.3.0
COMPONENT_LICENSE=	GPLv2
COMPONENT_GIT_REV=	348e202
COMPONENT_SRC=		kaizawa-$(COMPONENT_NAME)-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:72c9a7dc56cf52297ad163451df46f345a1c6019ba8fa84936e59550ab0f506e
COMPONENT_PROJECT_URL=	http://www.whiteboard.ne.jp/~admin2/tuntap/
COMPONENT_ARCHIVE_URL= 	https://codeload.github.com/kaizawa/tuntap/legacy.tar.gz/v$(COMPONENT_VERSION)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRUPT= $(@D)/configure

CONFIGURE_OPTIONS.32 = --disable-64bit

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)
