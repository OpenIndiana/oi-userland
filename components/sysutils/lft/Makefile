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
# Copyright 2014 (c) Aurelien Larcher. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         lft
COMPONENT_VERSION=      3.93
COMPONENT_SUMMARY=      Layer Four Traceroute (LFT) and WhoB
COMPONENT_PROJECT_URL=  https://pwhois.org/lft/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:132d74c1a8cf56023a16ddd39d10c89b4dfa0acdbd7c472e45ccc8521d8aaddd
COMPONENT_ARCHIVE_URL=	https://pwhois.org/dl/index.who?file=$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         diagnostic/lft
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=      VOSTROM Public License for Open Source

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Work around broken Makefile not supporting out of source build
COMPONENT_POST_CONFIGURE_ACTION= $(CP) $(SOURCE_DIR)/*.c $(SOURCE_DIR)/*.h $(SOURCE_DIR)/*.8 $(BUILD_DIR_$(BITS))/

COMPONENT_INSTALL_ARGS= DESTDIR=$(PROTO_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
