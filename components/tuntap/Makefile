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
COMPONENT_SRC_VERSION=	1.3
COMPONENT_SRC=		tun-$(COMPONENT_SRC_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:64668b7ae7eb60e7d8bce67ec83911ed7f72e19c5eda6fece2c2a0b0bb38bfb4
COMPONENT_PROJECT_URL=	http://www.whiteboard.ne.jp/~admin2/tuntap/
COMPONENT_ARCHIVE_URL=  https://github.com/joyent/illumos-extra/raw/master/tun/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRUPT= $(@D)/configure

CONFIGURE_OPTIONS.32 = --disable-64bit

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)
