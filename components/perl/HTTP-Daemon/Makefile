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
#   $WS_TOOLS/perl-integrate-module HTTP-Daemon
#

BUILD_STYLE = modulebuild

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		HTTP-Daemon
HUMAN_VERSION =			6.17
COMPONENT_SUMMARY =		A simple http server class
COMPONENT_CPAN_AUTHOR =		OALDERS
COMPONENT_ARCHIVE_HASH =	\
	sha256:16281580c40e23108d028434698b5d7d53637bf904c9df822481e253cbec920c
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENCE

include $(WS_MAKE_RULES)/common.mk

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# HTTP-Daemon --> libwww-perl --> HTTP-Daemon
#
# To break loops we need to allow this component to integrate without testing in
# a case the required packages are not available yet (bootstrap).
#
PERL_TEST_BOOTSTRAP = yes

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/http-date
REQUIRED_PACKAGES.perl += library/perl-5/http-message
REQUIRED_PACKAGES.perl += library/perl-5/io-socket-ip
REQUIRED_PACKAGES.perl += library/perl-5/lwp-mediatypes
REQUIRED_PACKAGES.perl += library/perl-5/module-build-tiny
REQUIRED_PACKAGES.perl += library/perl-5/socket
REQUIRED_PACKAGES.perl += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/cpan-meta
TEST_REQUIRED_PACKAGES.perl += library/perl-5/file-temp
TEST_REQUIRED_PACKAGES.perl += library/perl-5/libwww-perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/mime-base64
TEST_REQUIRED_PACKAGES.perl += library/perl-5/module-metadata
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-needs
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
