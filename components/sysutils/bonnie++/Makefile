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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= bonnie++
COMPONENT_VERSION= 1.97.3
COMPONENT_REVISION=	2
HUMAN_VERSION= $(COMPONENT_VERSION)
COMPONENT_SUMMARY= bonnie++ - Benchmark Harddrive utility
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
  sha256:e27b386ae0dc054fa7b530aab6bdead7aea6337a864d1f982bc9ebacb320746e
COMPONENT_ARCHIVE_URL= \
  http://www.coker.com.au/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.coker.com.au/bonnie++/

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

gcc_OPT= -O2

COMPONENT_BUILD_ARGS+= CXXFLAGS="$(gcc_OPT) $(CXXFLAGS)"
COMPONENT_BUILD_ARGS+= LDFLAGS="$(LDFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
