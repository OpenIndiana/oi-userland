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
COMPONENT_VERSION=      1.1.7
COMPONENT_SUMMARY=      Unit testing framework for C with support for mock objects
COMPONENT_PROJECT_URL=  https://cmocka.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:243344de12f8df78fa639fb426dd02d4cb37eda61462e48e6a0e13a98b94602a
COMPONENT_ARCHIVE_URL=	https://gitlab.com/cmocka/cmocka/-/archive/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/cmocka
COMPONENT_CLASSIFICATION=Development/C
COMPONENT_LICENSE=      Apache 2.0
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
