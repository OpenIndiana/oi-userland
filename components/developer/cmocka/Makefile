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
# Copyright 2022, Daniel Chan
# Copyright 2023, Niklas Poslovski
#

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         cmocka
COMPONENT_VERSION=      1.1.8
COMPONENT_SUMMARY=      Unit testing framework for C with support for mock objects
COMPONENT_PROJECT_URL=  https://cmocka.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:0994a7cd6b67c46b1cbfbb56c3b22ac379e1ac26fbe68e9cf7cea259b60e201c
COMPONENT_ARCHIVE_URL=	https://gitlab.com/cmocka/cmocka/-/archive/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/cmocka
COMPONENT_CLASSIFICATION=Development/C
COMPONENT_LICENSE=      Apache 2.0
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
