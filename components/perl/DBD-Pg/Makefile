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
# This file was automatically generated using the following command:
#   $WS_TOOLS/perl-integrate-module DBD-Pg
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		DBD-Pg
HUMAN_VERSION =			3.20.1
COMPONENT_SUMMARY =		DBI PostgreSQL interface
COMPONENT_CPAN_AUTHOR =		TURNSTEP
COMPONENT_ARCHIVE_HASH =	\
	sha256:1f5831745ee105a56e0bd2ab09b204a0f286461423c1eefe2a6d7be0ad91d024
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-2.0-only

include $(WS_MAKE_RULES)/common.mk

# force needed rpath
LD_OPTIONS += -R$(PG_LIBDIR)

# Make sure Postgres is always able to start (see README)
COMPONENT_TEST_ENV += DBDPG_TEMPDIR=/tmp

# Filter out line with Postgres version
COMPONENT_TEST_TRANSFORMS += '-e "/^Please wait, creating new database/d"'

# need pg_config at build time
REQUIRED_PACKAGES += $(PG_DEVELOPER_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.perl += library/perl-5/dbi
REQUIRED_PACKAGES.perl += library/perl-5/encode
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/file-temp
REQUIRED_PACKAGES.perl += library/perl-5/module-signature
REQUIRED_PACKAGES.perl += library/perl-5/test-simple
REQUIRED_PACKAGES.perl += library/perl-5/version
REQUIRED_PACKAGES.perl += runtime/perl
