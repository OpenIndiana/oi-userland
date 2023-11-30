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

COMPONENT_NAME=         perl
COMPONENT_VERSION_MAJOR =	5.34
COMPONENT_VERSION =		$(COMPONENT_VERSION_MAJOR).3
COMPONENT_SUMMARY =		Perl $(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://www.perl.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:0b15c830a9a295c9f9439b6cda389300f0b18092686eaef47fbc9c92f5930ee1
COMPONENT_ARCHIVE_URL=  https://www.cpan.org/src/5.0/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         runtime/perl-534
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_LICENSE=      Artistic
COMPONENT_LICENSE_FILE= Artistic

include $(WS_MAKE_RULES)/common.mk

# PERL_VERSION should be M.NN, it should not include the micro version
PERL_VERSION = $(COMPONENT_VERSION_MAJOR)

COMPONENT_BUILD_ARGS =

CONFIGURE_SCRIPT = $(SOURCE_DIR)/Configure
CONFIGURE_ENV += MAKE=$(GMAKE)

CONFIGURE_OPTIONS =	-de
CONFIGURE_OPTIONS +=	-Dmksymlinks
CONFIGURE_OPTIONS +=	-Ulocincpth=
CONFIGURE_OPTIONS +=	-Uloclibpth=

CONFIGURE_OPTIONS +=	-Dprefix=/usr/perl5/$(PERL_VERSION)
CONFIGURE_OPTIONS +=	-Dprivlib=/usr/perl5/$(PERL_VERSION)/lib
CONFIGURE_OPTIONS +=	-Dsitelib=/usr/perl5/site_perl/$(PERL_VERSION)
CONFIGURE_OPTIONS +=	-Dvendorprefix=/usr/perl5/$(PERL_VERSION)
CONFIGURE_OPTIONS +=	-Dvendorlib=/usr/perl5/vendor_perl/$(PERL_VERSION)
CONFIGURE_OPTIONS +=	-Dman3dir=/usr/perl5/$(PERL_VERSION)/man/man3perl
CONFIGURE_OPTIONS +=	-Dman3ext=3perl

CONFIGURE_OPTIONS +=	-Dmyhostname="localhost"
CONFIGURE_OPTIONS +=	-Dcf_email="oi-dev@openindiana.org"
CONFIGURE_OPTIONS +=	-Dcf_by="perl-bugs"

CONFIGURE_OPTIONS +=	-Duseshrplib
CONFIGURE_OPTIONS +=	-Dlibperl=libperl.so

CONFIGURE_OPTIONS +=	-Dusedtrace
CONFIGURE_OPTIONS +=	-Dusethreads
CONFIGURE_OPTIONS +=	-Duse64bitall

CONFIGURE_OPTIONS +=	-Dcc="$(CC) $(CC_BITS)"
CONFIGURE_OPTIONS +=	-Doptimize="$(gcc_OPT)"
CONFIGURE_OPTIONS +=	-Dlibpth="/lib/64 /usr/lib/64"


COMPONENT_INSTALL_ENV	+=	DESTDIR="$(PROTO_DIR)"

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

#
# Proper PERL_ARCH and PERLVER are needed for manifest processing.
#
PERL_ARCH = $(call PERL_ARCH_FUNC,$(PROTO_DIR)/usr/perl5/$(PERL_VERSION)/bin/perl)
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
