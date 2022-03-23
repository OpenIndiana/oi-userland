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
# Copyright (c) 2016 Aurelien Larcher
# Copyright (c) 2018 Michal Nowak
# Copyright (c) 2022 Andreas Wacknitz
#

X11_CATEGORY= LIB
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    libepoxy
COMPONENT_VERSION= 1.5.10
COMPONENT_FMRI=	   x11/library/libepoxy
COMPONENT_SUMMARY= library for handling OpenGL function pointers
COMPONENT_CLASSIFICATION=System/Hardware
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:a7ced37f4102b745ac86d6a70a9da399cc139ff168ba6b8002b4d8d43c900c15
COMPONENT_ARCHIVE_URL=	https://github.com/anholt/libepoxy/archive/refs/tags/$(COMPONENT_VERSION).tar.gz

include $(WS_MAKE_RULES)/common.mk

#CONFIGURE_OPTIONS += -Degl=no
CONFIGURE_OPTIONS += -Dtests=true

# Remove measured times (eg. 1.16s):
COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9].[0-9][0-9]s//" '

# Explicitly enable tests:
test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
