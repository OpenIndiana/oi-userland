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
# Copyright 2016 Gary Mills
# Copyright 2015 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	DBI-SQLite
COMPONENT_VERSION=	1.46
COMPONENT_SUMMARY= 	The DBI SQLite Interface for Perl
COMPONENT_SRC=		DBD-SQLite-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:b2b179136cd7c0df7b0e4840ff3f46330f161e5fc646279748afa7a3144f7cc0
#
# If this download fails, try a manual download from a web browser,
# using the same URL.  Verify that the hash is correct.  Then, copy
# the file to the archives directory.
COMPONENT_ARCHIVE_URL= \
  http://mirror.squ.edu.om/CPAN/modules/by-module/DBD/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://search.cpan.org/dist/DBD-SQLite/lib/DBD/SQLite.pm

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/makemaker.mk
include $(WS_TOP)/make-rules/ips.mk

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
