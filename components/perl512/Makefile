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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 32
include ../../make-rules/shared-macros.mk

PATH=$(dir $(CC)):$(USRBINDIR):$(GNUBIN)

# I want to override PERL_VERSION and PERL_ARCH because when building
# a new version of perl it probably isn't installed so shared-macros.mk
# can't call it.

COMPONENT_NAME=		perl
COMPONENT_VERSION=	5.12.5
PERL_VERSION=		5.12
COMPONENT_PROJECT_URL=	http://www.perl.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:10749417fd3010aae320a34181ad4cd6a4855c1fc63403b87fa4d630b18e966c
COMPONENT_ARCHIVE_URL=	http://www.cpan.org/src/5.0/$(COMPONENT_ARCHIVE)
TPNO=			9223

BUILD_TARGET=
INSTALL_TARGET=
TEST_TARGET=
include $(WS_MAKE_RULES)/common.mk

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

# Sparc optimization -xO4 makes perl dtrace probes broken
studio_OPT.sparc.32=-xO3

#
# The extra Configure parameters (cf_email, cf_by, myhostname) and
# the gawk and sed that follow are attempting to sanatize the
# resulting config.sh of values from our build environment that
# are discoverable in perl's config via "perl -V".
# I'm assuming our compilers live on a path that contains "SUNWspro".
# If that changes the sed filter needs to change.
#

PERLDIR=	$(USRDIR)/perl5
PERLLIBDIR=	$(PERLVERDIR)/lib
PERLVERDIR=	$(PERLDIR)/$(PERL_VERSION)
PERLSITEDIR=	$(PERLDIR)/site_perl/$(PERL_VERSION)
PERLVENDORDIR=	$(PERLDIR)/vendor_perl/$(PERL_VERSION)

CONFIGURE_SCRIPT = $(SOURCE_DIR)/Configure
CONFIGURE_ENV += MAKE=$(GMAKE)
CONFIGURE_ENV += PATH="$(PATH)"
CONFIGURE_OPTIONS = \
			    -Dprefix=$(PERLVERDIR) \
			    -Dprivlib=$(PERLLIBDIR) \
			    -Dsitelib=$(PERLSITEDIR) \
			    -Dvendorprefix=$(PERLVERDIR) \
			    -Dvendorlib=$(PERLVENDORDIR) \
			    -Dlibperl=libperl.so \
			    -Duseshrplib \
			    -Dusedtrace \
			    -Duse64bitint \
			    -Dcc="cc" \
			    -Doptimize="$(CFLAGS.studio)" \
			    -Dcf_by="perl-bugs" \
			    -Dmyhostname="localhost" \
			    -Dmksymlinks \
			    -O \
			    -de

CONFIGURE_THREAD_OPTIONS =  -Dusethreads \
			    -Duseithreads

COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D); \
	    cp config.sh config.sh_orig ; \
	    gawk \
	    '/^myuname=/{print $$1" localhost "$$3" "$$5" "$$6" "$$7"\047"} ; \
	    		!/^myuname=/ {print}' config.sh_orig \
		| \
		sed -e 's/[^ ]*SUNWspro[^ ]*//g' > config.sh )

COMPONENT_INSTALL_ENV	+=	DESTDIR="$(PROTO_DIR)"
#
# perl's install path for sparc is based off the value of the
# "arch" command.  So we must package that way also.
#
PKG_MACROS		+=	PERL_ARCH=$(shell arch)

#
# Put studio compilers in PATH so we can tell Configure and gmake just
# use cc.  Trying to avoid the full path so it doesn't end up in
# perl's config.
#
COMPONENT_BUILD_ENV	+=	PATH=$(dir $(CC.studio.32)):$(PATH)

# ST=single-thread.  MT=multi-thread.  The only difference in the build is that
# $(CONFIGURE_THREAD_OPTIONS) gets added to $(CONFIGURE_OPTIONS) in the MT case.
#
ST_VARIANT =	$(BUILD_DIR)/$(MACH32)-st
MT_VARIANT =	$(BUILD_DIR)/$(MACH32)-mt

VARIANTS =	$(MT_VARIANT) $(ST_VARIANT)

$(VARIANTS:%=%/.configured):	BITS=32

$(MT_VARIANT)/.configured:	CONFIGURE_OPTIONS += $(CONFIGURE_THREAD_OPTIONS)

BUILD_32 =	$(VARIANTS:%=%/.built)
INSTALL_32 =	$(VARIANTS:%=%/.installed)
TEST_32 =	$(VARIANTS:%=%/.tested)

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

# not yet tested with ASLR
ASLR_MODE= $(ASLR_DISABLE)

REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += developer/lexer/flex
REQUIRED_PACKAGES += developer/parser/bison
REQUIRED_PACKAGES += library/database/gdbm
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/groff/groff-core
