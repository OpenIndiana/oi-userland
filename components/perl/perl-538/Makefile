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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		perl
COMPONENT_VERSION =		5.38.0
COMPONENT_VERSION_MAJOR =	$(shell echo $(COMPONENT_VERSION) | $(GSED) -e 's/\(5\.[0-9]\{1,\}\)\..*/\1/g')
COMPONENT_SUMMARY =		Perl $(COMPONENT_VERSION_MAJOR)
COMPONENT_PROJECT_URL =		https://www.perl.org/
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH =	\
	sha256:eca551caec3bc549a4e590c0015003790bdd1a604ffe19cc78ee631d51f7072e
COMPONENT_ARCHIVE_URL =		https://www.cpan.org/src/5.0/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =		runtime/perl-$(shell echo $(COMPONENT_VERSION_MAJOR) | tr -d '.')
COMPONENT_CLASSIFICATION =	Development/Perl
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# PERL_VERSION should be M.NN, it should not include the micro version
PERL_VERSION = $(COMPONENT_VERSION_MAJOR)

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

CONFIGURE_OPTIONS +=	-Dcc="$(CC) $(CC_BITS)"
CONFIGURE_OPTIONS +=	-Doptimize="$(gcc_OPT)"
CONFIGURE_OPTIONS +=	-Dlibpth="/lib/64 /usr/lib/64"

COMPONENT_INSTALL_ENV	+=	DESTDIR="$(PROTO_DIR)"

COMPONENT_TEST_TRANSFORMS += "-e '1,/runtests choose/d'"	# throw out everything prior to test results
COMPONENT_TEST_TRANSFORMS += "-e '/^u=/d'"			# delete timings
COMPONENT_TEST_TRANSFORMS += "-e '/^Elapsed/d'"			# delete timings
COMPONENT_TEST_TRANSFORMS += "-e '/^make\[/d'"			# delete make logs

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
