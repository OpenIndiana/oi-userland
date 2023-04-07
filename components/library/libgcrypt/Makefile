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

BUILD_BITS= 32_and_64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgcrypt
COMPONENT_VERSION=	1.10.2
COMPONENT_SUMMARY=	GnuPG libgcrypt library
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/libgcrypt/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:3b9c02a004b68c256add99701de00b383accccf37177e0d6c58289664cce0c03
COMPONENT_ARCHIVE_URL=	ftp://ftp.gnupg.org/gcrypt/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		system/library/security/libgcrypt
COMPONENT_CLASSIFICATION= System/Security
COMPONENT_LICENSE=	LGPL, BSD, BSD-like

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

# We disalbe asm as this code doesn't compile.
# But libgcrypt still tries to use asm functions.
# gcry_cv_gcc_amd64_platform_as_ok switch allows us to prevent this
CONFIGURE_OPTIONS += --disable-asm
CONFIGURE_ENV += gcry_cv_gcc_amd64_platform_as_ok=no

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
