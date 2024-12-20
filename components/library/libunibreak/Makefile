#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2024 Andreas Wacknitz
#

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libunibreak
COMPONENT_VERSION= 6.1
COMPONENT_SUMMARY= Implementation of the line and word breaking algorithm for Unicode
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:cc4de0099cf7ff05005ceabff4afed4c582a736abc38033e70fdac86335ce93f
COMPONENT_ARCHIVE_URL=	https://github.com/adah1972/libunibreak/releases/download/libunibreak_6_1/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://vimgadgets.sourceforge.net/libunibreak/
COMPONENT_FMRI=			library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=		zlib/libpng licence
COMPONENT_LICENSE_FILE=	LICENCE

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --enable-static=no

COMPONENT_TEST_TRANSFORMS += \
	' -e "s/[0-9, ]*s//" ' \
	' -n ' \
	' -e "/Passed/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
