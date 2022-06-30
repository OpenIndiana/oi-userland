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

BUILD_STYLE = configure
BUILD_BITS = 64
USE_COMMON_TEST_MASTER = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		perl
COMPONENT_VERSION_MAJOR =	5.36
COMPONENT_VERSION =		$(COMPONENT_VERSION_MAJOR).0
COMPONENT_SUMMARY =		Perl $(COMPONENT_VERSION)
COMPONENT_PROJECT_URL =		https://www.perl.org/
COMPONENT_SRC =			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH =	\
	sha256:0f386dccbee8e26286404b2cca144e1005be65477979beb9b1ba272d4819bcf0
COMPONENT_ARCHIVE_URL =		https://www.cpan.org/src/5.0/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =		runtime/perl-536
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_LICENSE =		Artistic
COMPONENT_LICENSE_FILE =	Artistic

include $(WS_MAKE_RULES)/common.mk

# PERL_VERSION should be M.NN, it should not include the micro version
PERL_VERSION = $(COMPONENT_VERSION_MAJOR)

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
			-Duseshrplib \
			-Dusedtrace \
			-Dusethreads \
			-Dlibpth="/lib/64 /usr/lib/64"

COMPONENT_INSTALL_ENV	+=	DESTDIR="$(PROTO_DIR)"

#
# Throw out everything prior to test results.
# 2 x delete timings
#
COMPONENT_TEST_TRANSFORMS += \
	'-e "1,/runtests choose/d"' \
	'-e "/^u=/d" ' \
	'-e "/^Elapsed/d"'

#
# Proper PERL_ARCH and PERLVER are needed for manifest processing.
#
PERL_ARCH = $(shell . $(BUILD_DIR_$(BUILD_BITS))/config.sh && echo $$archname)
PKG_MACROS += PERLVER=$(PERL_VERSION)

#
# All hardlink targets should be listed here so generated sample manifest does
# not change with every run.
#
PKG_HARDLINKS += usr/perl5/$(PERL_VERSION)/bin/perl
PKG_HARDLINKS += usr/perl5/$(PERL_VERSION)/bin/perlbug
PKG_HARDLINKS += usr/perl5/$(PERL_VERSION)/man/man1/perlbug.1

# Auto-generated dependencies
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
