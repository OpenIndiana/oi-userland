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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2021, Tim Mooney.  All rights reserved.
#
BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

#
# Note this perl is 64-bit only.
#

# Override PERL_VERSION because when building a new version
# of perl it probably isn't installed so shared-macros.mk
# can't call it.

COMPONENT_NAME=         perl
COMPONENT_VERSION=      5.34.0
COMPONENT_SUMMARY=      Perl 5.34.0
# PERL_VERSION should be M.NN, it should not include the micro version
PERL_VERSION=		5.34
COMPONENT_PROJECT_URL=  https://www.perl.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:82c2e5e5c71b0e10487a80d79140469ab1f8056349ca8545140a224dbbed7ded
COMPONENT_ARCHIVE_URL=  https://www.cpan.org/src/5.0/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         runtime/perl-534
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_LICENSE=      Artistic
COMPONENT_LICENSE_FILE= Artistic

include $(WS_MAKE_RULES)/common.mk

LD_B_DIRECT=		""

COMPONENT_BUILD_ARGS =

CONFIGURE_SCRIPT = $(SOURCE_DIR)/Configure
CONFIGURE_ENV += MAKE=$(GMAKE)

CONFIGURE_OPTIONS = \
			-de \
			-Dmksymlinks \
			-Ulocincpth= \
			-Uloclibpth= \
			-Dbin=/usr/perl5/$(PERL_VERSION)/bin \
			-Dcc="$(CC) $(CC_BITS)" \
			-Dcf_email="oi-dev@openindiana.org" \
			-Dcf_by="perl-bugs" \
			-Dlibperl=libperl.so \
			-Dmyhostname="localhost" \
			-Dprefix=/usr/perl5/$(PERL_VERSION) \
			-Dprivlib=/usr/perl5/$(PERL_VERSION)/lib \
			-Dsitelib=/usr/perl5/site_perl/$(PERL_VERSION) \
			-Dsiteprefix=/usr/perl5/$(PERL_VERSION) \
			-Dvendorlib=/usr/perl5/vendor_perl/$(PERL_VERSION) \
			-Dvendorprefix=/usr/perl5/$(PERL_VERSION) \
			-Duse64bitall \
			-Duseshrplib \
			-Dusedtrace \
			-Dusethreads \
			-Dlibpth="/lib/64 /usr/lib/64"

COMPONENT_INSTALL_ENV	+=	DESTDIR="$(PROTO_DIR)"

#
# perl's install path for sparc is based off the value of the
# "arch" command.  So we must package that way also.
#
PKG_MACROS		+=	P_ARCH=$(shell arch)

#
# Getting 1 different result between sparc and x86.
#
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

#
# Throw out everything prior to test results.
# 2 x delete timings
#
COMPONENT_TEST_TRANSFORMS += \
	'-e "1,/runtests choose/d"' \
	'-e "/^u=/d" ' \
	'-e "/^Elapsed/d"'

# Auto-generated dependencies
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
