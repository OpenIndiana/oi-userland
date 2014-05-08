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
#
include ../../../make-rules/shared-macros.mk

#
# Note this perl is 32-bit only.
#

# I want to override PERL_VERSION and PERL_ARCH because when building
# a new version of perl it probably isn't installed so shared-macros.mk
# can't call it.

COMPONENT_NAME=		perl
COMPONENT_VERSION=	5.16.3
COMPONENT_REVISION=	1
PERL_VERSION=		5.16
COMPONENT_PROJECT_URL=	http://www.perl.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:bb7bc735e6813b177dcfccd480defcde7eddefa173b5967eac11babd1bfa98e8
COMPONENT_ARCHIVE_URL=	http://www.cpan.org/src/5.0/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/perl

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

LD_B_DIRECT=		""

#
# Override these compiler settings because they are causing problems
# in the ON build of the contrib components.
# ON doesn't use or need these settings or the compiler has some of them
# on by default.
# This also produces a perl more inline with past perl's.  For better
# or worse.
#

CONFIGURE_SCRIPT = $(SOURCE_DIR)/Configure
CONFIGURE_ENV += MAKE=$(GMAKE)
#CONFIGURE_ENV += PATH=$(dir $(CC)):$(PATH)

# -Dperl_static_inline="static" turns OFF "static inline".
# This was added because Configure probes
# for static inline (C99 feature) and finds it in our default Studio
# compiler.  But in the ON build of the perl add-ons, sun-solaris, the
# shadow build with gcc 3.4.3 doesn't understand static inline so errors.
#
CONFIGURE_OPTIONS = \
			-de \
			-Dmksymlinks \
			-Ulocincpth= \
			-Uloclibpth= \
                        -Dbin=/usr/perl5/$(PERL_VERSION)/bin \
			-Dcc="$(CC) $(CC_BITS)" \
			-Dcf_email="userland-discuss@opensolaris.org" \
			-Dcf_by="perl-bugs" \
			-Dlibperl=libperl.so \
			-Dmyhostname="localhost" \
			-Dperl_static_inline="static" \
			-Dprefix=/usr/perl5/$(PERL_VERSION) \
                        -Dprivlib=/usr/perl5/$(PERL_VERSION)/lib \
			-Dsitelib=/usr/perl5/site_perl/$(PERL_VERSION) \
			-Dsiteprefix=/usr/perl5/$(PERL_VERSION) \
			-Dvendorlib=/usr/perl5/vendor_perl/$(PERL_VERSION) \
			-Dvendorprefix=/usr/perl5/$(PERL_VERSION) \
			-Duse64bitint \
			-Duseshrplib \
			-Dusedtrace \
			-Uuselargefiles 

# The extra Configure parameters (cf_email, cf_by, myhostname) and
# the gawk and sed that follow are attempting to sanatize the
# resulting config.sh of values from our build environment that
# are discoverable in perl's config via "perl -V".
# I'm assuming our compilers live on a path that contains "SUNWspro".
# If that changes the sed filter needs to change.
#
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D); \
	    cp config.sh config.sh_orig ; \
	    gawk \
	    '/^myuname=/{print $$1" localhost "$$3" "$$5" "$$6" "$$7"\047"} ; \
	    		!/^myuname=/ {print}' config.sh_orig \
		| \
		sed -e "s/[^ ']*SUNWspro[^ ']*//g" > config.sh )


#
# Put studio compilers in PATH so we can tell Configure and gmake just
# use cc.  Trying to avoid the full path so it doesn't end up in
# perl's config.
#
# COMPONENT_BUILD_ENV	+=	PATH=$(dir $(CC)):$(PATH)
#COMPONENT_INSTALL_ENV	+=	PATH=$(dir $(CC)):$(PATH)
COMPONENT_INSTALL_ENV	+=	DESTDIR="$(PROTO_DIR)"
#COMPONENT_TEST_ENV	+=	PATH=$(dir $(CC)):$(PATH)

#
# perl's install path for sparc is based off the value of the
# "arch" command.  So we must package that way also.
#
PKG_MACROS		+=	P_ARCH=$(shell arch)

# Enable ASLR for this component
# ASLR_MODE = $(ASLR_ENABLE)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)
	#
	#
	# All tests should pass.
	#
	#

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
