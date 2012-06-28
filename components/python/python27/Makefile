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
include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		Python
COMPONENT_VERSION=	2.7.3
COMPONENT_PROJECT_URL=	http://python.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:726457e11cb153adc3f428aaf1901fc561a374c30e5e7da6742c0742a338663c
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)ftp/python/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/lint-libraries.mk

# We patch auto* files, so regenerate headers and configure
COMPONENT_PREP_ACTION = \
	(cd $(@D) ; autoheader ; autoconf)

# we don't want to leak $(CC_BITS) into BASECFLAGS as it causes problems with
# python-config
CC +=	$(CFLAGS)

C99MODE=
CPPFLAGS +=	-IPython

# to find the ncurses headers
CPPFLAGS +=	-I/usr/include/ncurses
# enable large files how they did in JDS
CPPFLAGS +=	-D_LARGEFILE64_SOURCE

# libffi for _ctypes
CPPFLAGS +=	$(shell pkg-config --cflags-only-I libffi)

# because python links with $(CC) ... $(LDFLAGS) ...
LDFLAGS =	$(CC_BITS) $(CC_PIC)

# build pic
CFLAGS +=	$(CC_PIC)

# The python build is profile-guided for studio; to see the benefits of that,
# Python must be compiled with -xO5 and a different build target must be used.
# Use of xprofile requires that the same options be used during compilation and
# linking.  The targets chosen are based on Solaris 11 minimum supported system
# requirements.
COMPONENT_BUILD_TARGETS = profile-opt
XPROFILE_DIR = $(BUILD_DIR_$(BITS))/.profile
# the non-clang compiler we need to use for now doesn't like
# this flag
#ifneq   ($(strip $(PARFAIT_BUILD)),yes)
PYFLAGS.i386 = -xtarget=opteron
#endif
PYFLAGS.i386 += -xarch=sse2 -xcache=generic
PYFLAGS.sparc =
CFLAGS += -xO5 $(PYFLAGS.$(MACH))
LDFLAGS += -xO5 $(PYFLAGS.$(MACH))

# add /usr/gnu/lib to the library search/run path
LDFLAGS.32 = -R/usr/gnu/lib -L/usr/gnu/lib
LDFLAGS.64 = -R/usr/gnu/lib/$(MACH64) -L/usr/gnu/lib/$(MACH64)
LDFLAGS += $(LDFLAGS.$(BITS))

# Python puts its header files in a special place.
LINT_FLAGS +=	-I$(SOURCE_DIR)/Include

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--with-system-expat
CONFIGURE_OPTIONS  +=		--with-system-ffi
CONFIGURE_OPTIONS  +=		--without-gcc
CONFIGURE_OPTIONS  +=		--enable-ipv6
CONFIGURE_OPTIONS  +=		ac_cv_opt_olimit_ok=no
CONFIGURE_OPTIONS  +=		ac_cv_olimit_ok=no
CONFIGURE_OPTIONS  +=		CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS  +=		LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		DFLAGS="-$(BITS)"
CONFIGURE_OPTIONS  +=		XPROFILE_DIR="$(XPROFILE_DIR)"

COMPONENT_BUILD_ENV  +=		DFLAGS="-$(BITS)"
COMPONENT_BUILD_ENV  +=		XPROFILE_DIR="$(XPROFILE_DIR)"

# patches/00-bits.patch removes some AC_CHECK_SIZEOF tests in order to
# generate a pyconfig.h that is both 32 and 64 bit compatible.  We add this
# back to the environment so that configure can still work.  configure.in and
# pyconfig.h.in should probably be rewhacked to do this more cleanly in the
# future.
CONFIGURE_OPTIONS.32  +=	ac_cv_sizeof_long=4
CONFIGURE_OPTIONS.64  +=	ac_cv_sizeof_long=8

# 64 bit shared objects need to go in a 64-bit directory
COMPONENT_INSTALL_ARGS.64 += DESTSHARED=$(CONFIGURE_PREFIX)/lib/python2.7/lib-dynload

# common targets
build:		$(BUILD_32_and_64)

$(INSTALL_32):	$(INSTALL_64)

install:	$(INSTALL_32_and_64)

COMPONENT_TEST_TARGETS = test

test:	$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
