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
#   $WS_TOOLS/perl-integrate-module DBD::MariaDB
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		DBD::MariaDB
HUMAN_VERSION =			1.23
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		DBD::MariaDB - MariaDB and MySQL driver for the Perl5 Database Interface (DBI)
COMPONENT_CPAN_AUTHOR =		PALI
COMPONENT_ARCHIVE_HASH =	\
	sha256:0d0c76c660ddd55570e48f3e2fdea8f621a69ac0ed48190e8cfcafcb5e9b859d
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# force needed rpath
LD_OPTIONS += -R$(MYSQL_LIBDIR)

# Configure needs to find mysqlclient library
COMPONENT_CONFIGURE_ENV += LD_LIBRARY_PATH=$(MYSQL_LIBDIR)

# need mysql_config at build time
REQUIRED_PACKAGES += $(MYSQL_CLIENT_PKG)

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/dbi
PERL_REQUIRED_PACKAGES += library/perl-5/devel-checklib
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.perl += library/perl-5/dbi
TEST_REQUIRED_PACKAGES.perl += library/perl-5/net-ssleay
TEST_REQUIRED_PACKAGES.perl += library/perl-5/proc-processtable
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-deep
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-pod
