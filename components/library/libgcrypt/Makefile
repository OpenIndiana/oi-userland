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
# Copyright 2013 Colin Ellis. All rights reserved.
# Copyright 2011 Audioboo Ltd. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgcrypt
COMPONENT_VERSION=	1.8.1
COMPONENT_FMRI=		system/library/security/libgcrypt
COMPONENT_SUMMARY=	GnuPG libgcrypt library
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/libgcrypt/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:7a2875f8b1ae0301732e878c0cca2c9664ff09ef71408f085c50e332656a78b3
COMPONENT_ARCHIVE_URL=	ftp://ftp.gnupg.org/gcrypt/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= System/Security
COMPONENT_LICENSE=	LGPL

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# GCC 5.3 (and 4.9) with the default optimization -O3 (set via shared-macros.mk),
# inlines _gcry_cipher_ocb_get_l, double_block_cpy and double_block to
# _gcry_cipher_ocb_authenticate on amd64. Due to a bug in GCC, the
# inlined code is incorrect and the library produces data with errors
# (manifested through failed 'basic' test results).  The optimization is
# lowered down on the affected platform.  For more information see:
# https://lists.gnupg.org/pipermail/gcrypt-devel/2016-April/003858.html
gcc_OPT.i386.64 = -O2

CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--sysconfdir=/etc

# We disalbe asm for 64-bit arch, as this code doesn't compile.
# But libgcrypt still tries to use asm functions.
# gcry_cv_gcc_amd64_platform_as_ok switch allows us to prevent this
CONFIGURE_OPTIONS.64  +=	--disable-asm
CONFIGURE_ENV.64 +=		gcry_cv_gcc_amd64_platform_as_ok=no

# some tests fail as gcry_control (GCRYCTL_INIT_SECMEM,...)
# requires root (or proc_lock_memory) privileges
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n -e "/PASS/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/All/p" '

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
