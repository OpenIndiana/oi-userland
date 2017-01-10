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

COMPONENT_NAME=		Archive-Zip
COMPONENT_VERSION=	1.37
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	http://search.cpan.org/dist/Archive-Zip/
COMPONENT_ARCHIVE_HASH=	\
    sha256:ba789436dc82db02a7f3d2e9d120d0221edc83d8c7ec72519648ae64bbc4ce05
COMPONENT_ARCHIVE_URL=	http://search.cpan.org/CPAN/authors/id/P/PH/PHRED/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/makemaker.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_TEST_TARGETS = test

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
