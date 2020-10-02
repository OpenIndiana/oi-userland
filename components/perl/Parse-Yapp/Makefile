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
# Copyright 2020 Rouven Weiler
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         Parse-Yapp
COMPONENT_VERSION=      1.21
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:3810e998308fba2e0f4f26043035032b027ce51ce5c8a52a8b8e340ca65f13e5
COMPONENT_ARCHIVE_URL= \
  https://cpan.metacpan.org/authors/id/W/WB/WBRASWELL/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://metacpan.org/release/Parse-Yapp/source/lib/Parse/Yapp.pm

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/makemaker.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_TEST_TARGETS = test

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
