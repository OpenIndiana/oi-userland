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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018 Norm Jacobs
# Copyright (c) 2018 Ken Mays
# Copyright (c) 2020 Michal Nowak
# Copyright (c) 2022 Klaus Ziegler
#

BUILD_BITS= 64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		binutils
COMPONENT_VERSION=	2.38
COMPONENT_SUMMARY=	GNU collection of binary tools like ld, as
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/binutils/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:e316477a914f567eccc34d5d29785b8b0f5a10208d36bbacedcc39048ecfe024
COMPONENT_FMRI=		developer/gnu-binutils
COMPONENT_CLASSIFICATION=Development/GNU

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_PREFIX =	/usr/gnu

# Since gcc-9 the GNU triple is x86_64-pc-solaris2.11 instead of i386-pc-solaris2.11
GNU_TRIPLET=$(shell $(CC) -dumpmachine)

CONFIGURE_OPTIONS +=	--mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	--enable-64-bit-bfd
CONFIGURE_OPTIONS +=    --enable-gold=no
CONFIGURE_OPTIONS +=    --enable-plugins=yes
CONFIGURE_OPTIONS +=    --enable-nls
CONFIGURE_OPTIONS +=    --disable-libtool-lock
CONFIGURE_OPTIONS +=    --enable-largefile=yes
CONFIGURE_OPTIONS +=	--with-system-zlib
CONFIGURE_OPTIONS +=    --host=$(GNU_TRIPLET)
CONFIGURE_OPTIONS +=    --build=$(GNU_TRIPLET)
CONFIGURE_OPTIONS +=    --target=$(GNU_TRIPLET)

COMPONENT_TEST_ARGS += -k

# Keep only the test results.  Details are always in the build directory
COMPONENT_TEST_TRANSFORMS += \
	'-n '\
	'-e "/^\# of/p" '\
	'-e "/Summary =/p" '

# Master test results are different between amd64 and SPARCV9.
COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH64).master

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
