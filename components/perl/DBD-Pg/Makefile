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
#   $WS_TOOLS/perl-integrate-module DBD::Pg
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		DBD::Pg
HUMAN_VERSION =			3.16.3
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		DBD::Pg - PostgreSQL database driver for the DBI module
COMPONENT_CPAN_AUTHOR =		TURNSTEP
COMPONENT_ARCHIVE_HASH =	\
	sha256:8872f13034b6f9f0c7e08f9a6edf2bb0ae53b8eb51f1959e9d568d9c4dd8d57c
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-2.0-only

# Don't depend on host default pg_config
PATH = $(PG_BINDIR):$(PATH.illumos)

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
PERL_REQUIRED_PACKAGES += library/perl-5/dbi
PERL_REQUIRED_PACKAGES += library/perl-5/module-signature
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += $(PG_LIBRARY_PKG)
REQUIRED_PACKAGES += system/library
