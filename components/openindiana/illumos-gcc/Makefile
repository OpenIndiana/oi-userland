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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		illumos-gcc
COMPONENT_VERSION=	4.4.4
COMPONENT_REVISION=	6
COMPONENT_SUMMARY=	GCC - 4.4.4 compilers patched for illumos
COMPONENT_SRC=		illumos-gcc-0f5ed4c
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e87531b5f9c15c3a3d07f8e50acfb787a807174cafd38590e6f9a3da646b7ac6
ILLUMOS_VERSION=	gcc-4.4.4-il-4
COMPONENT_ARCHIVE_URL=	https://github.com/illumos/gcc/tarball/$(ILLUMOS_VERSION)
COMPONENT_PROJECT_URL=	https://github.com/illumos/gcc
COMPONENT_FMRI=		developer/illumos-gcc
COMPONENT_CLASSIFICATION=	Development/C
COMPONENT_LICENSE=	GPLv3 with Runtime Exception, FDLv1.2
COMPONENT_LICENSE_FILE=	gcc.license


MPFR_NAME= mpfr
MPFR_VERSION=3.1.2
COMPONENT_SRC_1=    $(MPFR_NAME)-$(MPFR_VERSION)
COMPONENT_ARCHIVE_1=    $(COMPONENT_SRC_1).tar.bz2
COMPONENT_ARCHIVE_URL_1= http://www.mpfr.org/$(COMPONENT_SRC_1)/$(COMPONENT_ARCHIVE_1)
COMPONENT_SIG_URL_1= $(COMPONENT_ARCHIVE_URL_1).asc
COMPONENT_ARCHIVE_HASH_1= \
    sha256:79c73f60af010a30a5c27a955a1d2d01ba095b72537dab0ecaad57f5a7bb1b6b
CLEAN_PATHS += $(COMPONENT_SRC_1)
COMPONENT_POST_UNPACK_ACTION_1 += ( $(RM) -r $(COMPONENT_SRC)/$(MPFR_NAME) && $(CP) -rpP $(COMPONENT_SRC_1) $(COMPONENT_SRC)/$(MPFR_NAME) )

MPC_NAME=mpc
MPC_VERSION=1.0.1
COMPONENT_SRC_2= $(MPC_NAME)-$(MPC_VERSION)
COMPONENT_ARCHIVE_2= $(COMPONENT_SRC_2).tar.gz
COMPONENT_ARCHIVE_URL_2=  https://ftp.gnu.org/gnu/mpc/$(COMPONENT_ARCHIVE_2)
COMPONENT_SIG_URL_2=	$(COMPONENT_ARCHIVE_URL_2).sig 
COMPONENT_ARCHIVE_HASH_2= \
    sha256:ed5a815cfea525dc778df0cb37468b9c1b554aaf30d9328b1431ca705b7400ff
CLEAN_PATHS += $(COMPONENT_SRC_2)
COMPONENT_POST_UNPACK_ACTION_2 += ( $(RM) -r $(COMPONENT_SRC)/$(MPC_NAME) && $(CP) -rpP $(COMPONENT_SRC_2) $(COMPONENT_SRC)/$(MPC_NAME) )

GMP_NAME=gmp
GMP_VERSION=5.0.5
COMPONENT_SRC_3= $(GMP_NAME)-$(GMP_VERSION)
COMPONENT_ARCHIVE_3= $(COMPONENT_SRC_3).tar.bz2
COMPONENT_ARCHIVE_URL_3=  http://ftp.gnu.org/gnu/gmp/$(COMPONENT_ARCHIVE_3)
COMPONENT_SIG_URL_3=	$(COMPONENT_ARCHIVE_URL_3).sig 
COMPONENT_ARCHIVE_HASH_3= \
    sha256:1f588aaccc41bb9aed946f9fe38521c26d8b290d003c5df807f65690f2aadec9
CLEAN_PATHS += $(COMPONENT_SRC_3)
COMPONENT_POST_UNPACK_ACTION_3 += ( $(RM) -r $(COMPONENT_SRC)/$(GMP_NAME) && $(CP) -rpP $(COMPONENT_SRC_3) $(COMPONENT_SRC)/$(GMP_NAME) )

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

GCC_VERSION=4.9

CC_BITS=
CFLAGS=		-g -O2
CONFIG_SHELL=	/bin/sh

CONFIGURE_PREFIX=	/opt/gcc/$(COMPONENT_VERSION)

# sparc and x86 use different assemblers
CONFIGURE_OPTIONS.sparc +=	--without-gnu-as --with-as=/usr/bin/as
CONFIGURE_OPTIONS.i386 +=	--with-gnu-as --with-as=/usr/sfw/bin/gas

CONFIGURE_OPTIONS  =	--prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS +=	$(CONFIGURE_OPTIONS.$(MACH))
CONFIGURE_OPTIONS +=	--with-ld=/usr/bin/ld
CONFIGURE_OPTIONS +=	--without-gnu-ld
CONFIGURE_OPTIONS +=	--enable-languages="c,c++,objc"
CONFIGURE_OPTIONS +=	--enable-shared
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

# Build dependencies
REQUIRED_PACKAGES += developer/gcc-49

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
