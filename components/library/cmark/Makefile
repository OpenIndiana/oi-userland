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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE = cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cmark
COMPONENT_VERSION=      0.30.3
COMPONENT_PROJECT_URL=  https://github.com/commonmark/cmark
COMPONENT_SUMMARY=      CommonMark parsing and rendering library and program in C
COMPONENT_FMRI=         library/cmark
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:85e9fb515531cc2c9ae176d693f9871774830cf1f323a6758fb187a5148d7b16
COMPONENT_ARCHIVE_URL=	https://github.com/commonmark/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION=       System/Libraries
COMPONENT_LICENSE=      Custom
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMARK_STATIC=OFF

COMPONENT_TEST_TRANSFORMS += '-e "s/ [0-9].[0-9][0-9] sec//" '
COMPONENT_TEST_TRANSFORMS += '-e "s/ [0-9][0-9].[0-9][0-9] sec//" '
COMPONENT_TEST_TRANSFORMS += '-e "s/ [0-9][0-9][0-9].[0-9][0-9] sec//" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
