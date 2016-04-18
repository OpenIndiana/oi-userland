#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		DBD-SQLite
COMPONENT_VERSION=	1.48
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:b397230f5d4cdc9923f91c62da9e535234f3055c528ede75afd7d24698030ea6
COMPONENT_ARCHIVE_URL=	http://backpan.perl.org/authors/id/I/IS/ISHIGAKI/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://github.com/DBD-SQLite/DBD-SQLite
COMPONENT_BUGDB=	perl-mod/dbd-sqlite

TPNO=			24450

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/makemaker.mk

COMPONENT_TEST_TARGETS = test
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-e "/^Running Mkbootstrap/d" ' \
	'-e "s/[0-9][0-9]* wallclock secs (.*CPU)$$/<TIMINGS REMOVED>/" ' \
	'-e "/^PERL_DL_NONLAZY/d" ' \
	'-e "s/^\(\# sqlite_version=\)[0-9][0-9.]*/\1<USED SQLITE VERSION REMOVED>/" ' \
	'-e "s/^\(\# \$$DBI::VERSION=\)[0-9][0-9.]*/\1<REPORTED DBI VERSION REMOVED>/" ' \
	'-e "/^chmod/d" '

# This makes the configuration process a bit more chatty
COMPONENT_CONFIGURE_ENV += AUTOMATED_TESTING=1

LICENSE=DBD-SQLite.license
CLEAN_PATHS += $(LICENSE)

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

$(LICENSE): $(LICENSE).template
	$(PERL) -pe 's/COMPONENT_VERSION/$(COMPONENT_VERSION)/g' "$<" > "$@"

# DBI must be installed to build
build:		$(BUILD_64) \
		$(LICENSE)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/perl-5/database
REQUIRED_PACKAGES += system/library
