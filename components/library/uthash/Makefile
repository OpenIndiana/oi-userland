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
# Copyright 2021 Benjamin S. Osenbach
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		uthash
COMPONENT_VERSION=	2.4.0
COMPONENT_SUMMARY= 	uthash is a hash table for C structures
COMPONENT_PROJECT_URL=	https://github.com/troydhanson/uthash
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/troydhanson/uthash/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:387ba027946d7c64e9aa19cc53b2edcd714f8f9dca9fa8e3aaef17e0e8e3d736
COMPONENT_FMRI=		library/uthash
COMPONENT_CLASSIFICATION= Development/C
COMPONENT_LICENSE= BSD
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR = $(@D)/tests
COMPONENT_TEST_CMD = $(GMAKE)
COMPONENT_TEST_TARGETS = pedantic
COMPONENT_TEST_ENV += PATH=$(PATH.gnu)

# Auto-generated dependencies
