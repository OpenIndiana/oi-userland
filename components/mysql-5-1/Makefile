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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		mysql
COMPONENT_VERSION=	5.1.37
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:6a4596462d4447a79a0ad607ea1475ba0599651e2d82305a7f7dade038827f0c
COMPONENT_ARCHIVE_URL=	http://downloads.mysql.com/archives/mysql-5.1/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://dev.mysql.com/ 

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL=0

COMPONENT_PRE_CONFIGURE_ACTION = \
        ( cd $(COMPONENT_SRC) ; \
        $(TOUCH) configure.in config/ac-macros/* ; sleep 5 ; \
        $(TOUCH) aclocal.m4 config.h.in ; sleep 5 ; \
        $(TOUCH) configure ; sleep 5 ; \
        /usr/bin/find . -name Makefile.in | /usr/bin/xargs $(TOUCH) ; \
        /usr/bin/find . -type d -exec $(CHMOD) 755 "{}" \; ; \
        /usr/bin/find . -type f -exec $(CHMOD) ugo+r "{}" \; ; \
        )

CONFIGURE_PREFIX=/usr/mysql/5.1
CONFDIR=/etc/mysql/5.1
DATA_PREFIX=/var/mysql/5.1
CONFIGURE_MANDIR=$(CONFIGURE_PREFIX)/man

# Although -norunpath is set in CXXFLAGS, we need to append
# the -norunpath option here, so it's picked up when building
# shared libraries (CC -G)
CXX += $(studio_NORUNPATH)

# C common compiler flags
CFLAGS += -xstrconst -xprefetch=auto -xprefetch_level=3 -fns=no -fsimple=1 -xbuiltin=%none \
-xlibmil -xlibmopt -xnorunpath 

# C++ common compiler flags
CXXFLAGS += -DDBUG_OFF -noex -DBIG_TABLES -DHAVE_RWLOCK_T $(CC_PIC) $($(COMPILER)_opt) \
$($(COMPILER)_MT) -xprefetch=auto -xprefetch_level=3 -fns=no -fsimple=1 -xbuiltin=%none \
-xlibmil -xlibmopt

#build environment common to both 32 & 64bit builds
COMPONENT_BUILD_ENV +=	CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV +=	LDFLAGS="$(LDFLAGS)"

# build environment applicable to only 32bit
COMPONENT_BUILD_ENV.32 +=	CXXFLAGS="$(CXXFLAGS)" 

#build environment applicable to only 64bit
COMPONENT_BUILD_ENV.64 +=       CXXFLAGS="$(CXXFLAGS) -features=no%except" 

#common configure options for both 32 & 64bits
CONFIGURE_OPTIONS +=	ac_cv_func_stpcpy=no
CONFIGURE_OPTIONS += 	--localstatedir=$(DATA_PREFIX)/data	
CONFIGURE_OPTIONS +=	--datadir=$(CONFIGURE_PREFIX)/share	
CONFIGURE_OPTIONS += 	--sharedstatedir=$(CONFIGURE_PREFIX)/com	
CONFIGURE_OPTIONS += 	--includedir=$(CONFIGURE_PREFIX)/include	
CONFIGURE_OPTIONS += 	--oldincludedir=$(CONFIGURE_PREFIX)/include	
CONFIGURE_OPTIONS += 	--infodir=$(CONFIGURE_PREFIX)/docs	
CONFIGURE_OPTIONS += 	--sysconfdir=$(CONFDIR)	
CONFIGURE_OPTIONS +=	--enable-thread-safe-client
CONFIGURE_OPTIONS +=	--with-mysqld-libs=-lmtmalloc
CONFIGURE_OPTIONS +=	--with-client-ldflags=-static
CONFIGURE_OPTIONS +=	--with-mysqld-ldflags=-static	
CONFIGURE_OPTIONS +=	--with-pic
CONFIGURE_OPTIONS +=	--with-big-tables
CONFIGURE_OPTIONS +=	--with-ssl
CONFIGURE_OPTIONS +=	--with-readline
CONFIGURE_OPTIONS +=	--with-extra-charsets=complex
CONFIGURE_OPTIONS +=	--with-plugins=archive,blackhole,csv,myisam,example,federated,innobase,myisammrg
CONFIGURE_OPTIONS +=	--enable-local-infile
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS +=	studio_NORUNPATH="$(studio_NORUNPATH)"	

CONFIGURE_OPTIONS.32 +=	--libexecdir=$(CONFIGURE_PREFIX)/bin
CONFIGURE_OPTIONS.32 +=	--enable-dtrace DTRACEFLAGS='-32'
	
CONFIGURE_OPTIONS.64 += --libexecdir=$(CONFIGURE_PREFIX)/bin/$(MACH64)	
CONFIGURE_OPTIONS.64 += --enable-dtrace DTRACEFLAGS='-64'	

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
