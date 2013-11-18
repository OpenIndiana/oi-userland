#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2012, Jon Tibble
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		illumos-gcc
COMPONENT_VERSION=	4.4.4
COMPONENT_SRC=		illumos-gcc-bcf43dd
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:373d39fe19299da26e0a4e124e1a2f97565a2535c8fabf9bd075a0e6fda050e1
ILLUMOS_VERSION=	gcc-4.4.4-il-3
COMPONENT_ARCHIVE_URL=	https://github.com/illumos/gcc/tarball/$(ILLUMOS_VERSION)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CC_BITS=
CFLAGS=		-g -O2
CONFIG_SHELL=	/bin/sh

CONFIGURE_PREFIX=	/opt/gcc/$(COMPONENT_VERSION)

PARCH = $(MACH:i386=i386-pc)
GNU_ARCH = $(PARCH:sparc=sparc-sun)-solaris$(SOLARIS_VERSION)
PKG_MACROS += GNU_ARCH="$(GNU_ARCH)"

# sparc and x86 use different assemblers
CONFIGURE_OPTIONS.sparc +=	--without-gnu-as --with-as=/usr/bin/as
CONFIGURE_OPTIONS.i386 +=	--with-gnu-as --with-as=/usr/sfw/bin/gas

CONFIGURE_OPTIONS =	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	$(CONFIGURE_OPTIONS.$(MACH))
CONFIGURE_OPTIONS +=	--with-ld=/usr/bin/ld
CONFIGURE_OPTIONS +=	--without-gnu-ld
CONFIGURE_OPTIONS +=	--enable-languages="c,c++,objc"
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--with-mpfr-include=/usr/include/mpfr
CONFIGURE_OPTIONS +=	--with-gmp-include=/usr/include/gmp
CONFIGURE_OPTIONS +=	--with-pkgversion="Illumos $(ILLUMOS_VERSION)"
CONFIGURE_OPTIONS +=	--with-bugurl="http://github.com/illumos/gcc/issues"

COMPONENT_BUILD_ENV=		SHELL=$(CONFIG_SHELL) CFLAGS="$(CFLAGS)" STAGE1_CFLAGS="$(CFLAGS)" CFLAGS_FOR_TARGET="$(CFLAGS)"
COMPONENT_BUILD_GMAKE_ARGS=	-j8
COMPONENT_BUILD_TARGETS=	bootstrap

COMPONENT_POST_INSTALL_ACTION= ( \
	elfedit -e 'dyn:rpath /opt/gcc/4.4.4/lib' $(PROTO_DIR)/opt/gcc/4.4.4/lib/libgomp.so.1 ; \
	elfedit -e 'dyn:rpath /opt/gcc/4.4.4/lib/amd64' $(PROTO_DIR)/opt/gcc/4.4.4/lib/amd64/libgomp.so.1 ; \
	elfedit -e 'dyn:rpath /opt/gcc/4.4.4/lib' $(PROTO_DIR)/opt/gcc/4.4.4/lib/libssp.so.0 ; \
	elfedit -e 'dyn:rpath /opt/gcc/4.4.4/lib/amd64' $(PROTO_DIR)/opt/gcc/4.4.4/lib/amd64/libssp.so.0 ; \
	elfedit -e 'dyn:rpath /opt/gcc/4.4.4/lib' $(PROTO_DIR)/opt/gcc/4.4.4/lib/libstdc++.so.6 ; \
	elfedit -e 'dyn:rpath /opt/gcc/4.4.4/lib/amd64' $(PROTO_DIR)/opt/gcc/4.4.4/lib/amd64/libstdc++.so.6 )

build:		$(BUILD_32)

install:	$(INSTALL_32)
