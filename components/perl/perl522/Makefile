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

#
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		perl
COMPONENT_VERSION=	5.22.1
PERL_VERSION_LOCAL=	5.22
COMPONENT_PROJECT_URL=	http://www.perl.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
     sha256:e98e4075a3167fa40524abe447c30bcca10c60e02a54ee1361eff278947a1221
COMPONENT_ARCHIVE_URL=	http://www.cpan.org/src/5.0/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/perl
TPNO=			26810

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(SPRO_VROOT)/bin:/usr/bin
endif

#
# Override these compiler settings because they are causing problems
# in the ON build of the contrib components.
# ON doesn't use or need these settings or the compiler has some of them
# on by default.
# This also produces a perl more inline with past perl's.  For better
# or worse.
#
studio_XBITS=
studio_XREGS=
studio_IROPTS=
studio_C99MODE=
studio_ALIGN=
studio_MT=

# Sparc optimization -xO4 causes issues with dtrace probes on Sparc
studio_OPT.sparc.64=-xO3

CONFIGURE_SCRIPT = $(SOURCE_DIR)/Configure
CONFIGURE_ENV += MAKE=$(GMAKE)
CONFIGURE_ENV += PATH=$(dir $(CC)):$(PATH)

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
                        -Dbin=/usr/perl5/$(PERL_VERSION_LOCAL)/bin \
			-Dcc="cc" \
			-Dcf_by="perl-bugs" \
			-Dlibperl=libperl.so \
			-Dmyhostname="localhost" \
			-Dperl_static_inline="static" \
			-Dprefix=/usr/perl5/$(PERL_VERSION_LOCAL) \
                        -Dprivlib=/usr/perl5/$(PERL_VERSION_LOCAL)/lib \
			-Dsitelib=/usr/perl5/site_perl/$(PERL_VERSION_LOCAL) \
			-Dsiteprefix=/usr/perl5/$(PERL_VERSION_LOCAL) \
			-Dvendorlib=/usr/perl5/vendor_perl/$(PERL_VERSION_LOCAL) \
			-Dvendorprefix=/usr/perl5/$(PERL_VERSION_LOCAL) \
			-Duseshrplib \
			-Dusedtrace \
			-Duse64bitall \
                        -Dusethreads \
			-Dlibpth="/lib/64 /usr/lib/64" \
			-Dusesitecustomize \
			-Doptimize="$(CFLAGS.studio)"

#
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
COMPONENT_BUILD_ENV	  +=	PATH=$(dir $(CC)):$(PATH)
COMPONENT_INSTALL_ENV	  +=	PATH=$(dir $(CC)):$(PATH)
COMPONENT_INSTALL_ENV	  +=	DESTDIR="$(PROTO_DIR)"
COMPONENT_TEST_ENV	  +=	PATH=$(dir $(CC)):$(PATH)
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
# perl's install path for sparc is based off the value of the
# "arch" command.  So we must package that way also.
#
PKG_MACROS 		+=	P_ARCH=$(shell arch)
PKG_MACROS		+=	PERL_VERSION=$(PERL_VERSION_LOCAL)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

parfait:	PARFAIT_BUILD=yes install

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
