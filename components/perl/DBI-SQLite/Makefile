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
# copyright 2022 (c) Tim Mooney.  All rights reserved.
#

BUILD_STYLE=makemaker
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	DBI-SQLite
COMPONENT_VERSION=	1.52
COMPONENT_REVISION=	3
COMPONENT_SUMMARY= 	The DBI SQLite Interface for Perl
COMPONENT_FMRI=		library/perl-5/sqlite-dbi
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_PROJECT_URL = https://metacpan.org/pod/DBD::SQLite
COMPONENT_SRC=		DBD-SQLite-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:a6da099e9b953262afafea18335930bede1f195fdead45bd3f00e690b158354e
COMPONENT_ARCHIVE_URL= \
  http://cpan.metacpan.org/authors/id/I/IS/ISHIGAKI/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	Artistic
COMPONENT_LICENSE_FILE=	dbi-sqlite.license

# until all perl modules have been rebuilt with 5.34, each module sets
# this manually, before including common.mk
PERL_VERSIONS = 5.22 5.24 5.34
PERL_64_ONLY_VERSIONS = 5.24 5.34

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

include $(WS_MAKE_RULES)/common.mk

#
# need different results per version because 5.24+ has threading while
# 5.22 does not.
#
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(PERL_VERSION).master

#
# filter out all output up to and including the test_harness line
# filter out timing information and anything else that varies between builds
# also remove a couple of version numbers to reduce spurious test diffs
#
COMPONENT_TEST_TRANSFORMS += \
	'-e "1,/test_harness/d"' \
	'-e "s/,  *[0-9]* wallclock.*//"' \
	'-e "s/DBI::VERSION=.*/DBI::VERSION=removed for test uniformity/"' \
	'-e "s/sqlite_version=.*/sqlite_version=removed for test uniformity/"'

# database/sqlite-3 is not required, either at build time or runtime.
# DBD::SQLite includes its own copy of the source and builds SQLite into
# its own shared object.

# build and runtime dependency on perl's DBI module
REQUIRED_PACKAGES += library/perl-5/database

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
REQUIRED_PACKAGES += system/library
