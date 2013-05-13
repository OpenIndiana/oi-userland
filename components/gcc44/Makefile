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
# Copyright (c) 2011, OpenIndiana project. All rights reserved.
# Copyright (c) 2012, Bayard G. Bell. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gcc
COMPONENT_VERSION=	4.4.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:e1c13696b45752ad3f652304fab5120a43a8a5c0f438d3bda78cf16b620c0c58	
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/gcc/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://gcc.gnu.org/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/perl5/bin
GCC44_ROOT=	/usr/gcc/4.4
COMPILER=	gcc

# workaround while ALTPLAT/PKG_MACROS fix pending
PLAT=$(shell uname -p | sed 's/i386/pc/;s/sparc/sun/')
PKG_MACROS += PLAT=$(PLAT)

ifndef GCC_BOOTSTRAP
GCC_ROOT=		$(GCC44_ROOT)
endif

CPPFLAGS+= -fexceptions

CONFIGURE_PREFIX    =           $(GCC44_ROOT)
CONFIGURE_OPTIONS  +=           CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS  +=		--with-gmp-include=/usr/include/gmp/
CONFIGURE_OPTIONS  +=		--with-mpfr-include=/usr/include/mpfr/
CONFIGURE_OPTIONS  +=           --without-ppl
CONFIGURE_OPTIONS  +=           --without-cloog
CONFIGURE_OPTIONS  +=           --with-gnu-as
CONFIGURE_OPTIONS  +=		--with-as=$(SFWBIN)/gas
CONFIGURE_OPTIONS  +=           --with-ld=/usr/ccs/bin/ld
CONFIGURE_OPTIONS  +=           --enable-stage1-languages=c
CONFIGURE_OPTIONS  +=           --enable-languages=c,c++,objc,fortran
CONFIGURE_OPTIONS  +=           --build=$(MACH)-$(PLAT)-solaris$(SOLARIS_VERSION)
ifdef GCC_BOOTSTRAP
CONFIGURE_OPTIONS  +=		--enable-bootstrap
COMPONENT_BUILD_TARGETS  =	bootstrap
endif

COMPONENT_BUILD_ENV  +=		SHELL=$(CONFIG_SHELL)

# We use manifest includes and want them not to depend on PWD
PKG_OPTIONS += -I $(COMPONENT_DIR)

include $(WS_TOP)/make-rules/shared-targets.mk

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TEST)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
