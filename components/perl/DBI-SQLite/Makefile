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
# Copyright 2015 Josef 'Jeff' Sipek <jeffpc@josefsipek.net>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	DBI-SQLite
COMPONENT_VERSION=	1.52
COMPONENT_SUMMARY= 	The DBI SQLite Interface for Perl
COMPONENT_SRC=		DBD-SQLite-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:a6da099e9b953262afafea18335930bede1f195fdead45bd3f00e690b158354e
COMPONENT_ARCHIVE_URL= \
  http://search.cpan.org/CPAN/authors/id/I/IS/ISHIGAKI/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://search.cpan.org/dist/DBD-SQLite/lib/DBD/SQLite.pm

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/makemaker.mk
include $(WS_TOP)/make-rules/ips.mk

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += library/perl-5/database
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
