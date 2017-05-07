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
# Copyright 2016 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           ck
COMPONENT_VERSION=        0.5.2
COMPONENT_SUMMARY=        ck - Concurrency Kit
COMPONENT_DESCRIPTION=    Concurrency primitives, safe memory reclamation mechanisms and non-blocking data structures for the research, design and implementation of high performance concurrent systems.
COMPONENT_PROJECT_URL=    http://concurrencykit.org/
COMPONENT_FMRI=           library/ck
COMPONENT_CLASSIFICATION= System/Libraries  
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=    http://concurrencykit.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:5cf44b33f9279c653ec9b2b085d628c86336e4da18897be449f074283e5c5b3a
COMPONENT_LICENSE=        BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS+= --includedir=$(USRINCDIR)/$(COMPONENT_NAME)
CONFIGURE_OPTIONS+= --environment=$(BITS)

COMPONENT_TEST_TARGETS= regressions

build:    $(BUILD_32_and_64)

install:  $(INSTALL_32_and_64)

# Tests are not supported out-of-source for now
test:    $(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
