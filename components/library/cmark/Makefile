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

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cmark
COMPONENT_VERSION=      0.31.0
COMPONENT_SUMMARY=      CommonMark parsing and rendering library and program in C
COMPONENT_PROJECT_URL=  https://github.com/commonmark/cmark
COMPONENT_FMRI=         library/cmark
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:bbcb8f8c03b5af33fcfcf11a74e9499f20a9043200b8552f78a6e8ba76e04d11
COMPONENT_ARCHIVE_URL=	https://github.com/commonmark/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=      Custom
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMARK_STATIC=OFF

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
