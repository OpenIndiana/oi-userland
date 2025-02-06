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
# Copyright 2019 Michal Nowak
#

BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgpg-error
COMPONENT_VERSION=	1.51
COMPONENT_SUMMARY=	GnuPG Error Library
COMPONENT_PROJECT_URL=	https://www.gnupg.org/related_software/libgpg-error/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:be0f1b2db6b93eed55369cdf79f19f72750c8c7c39fc20b577e724545427e6b2
COMPONENT_ARCHIVE_URL=	https://gnupg.org/ftp/gcrypt/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/security/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Security
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING.LIB

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS += $(XPG6MODE)
CFLAGS += -D_POSIX_PTHREAD_SEMANTICS

COMPONENT_PREP_ACTION= ( cd $(@D) && PATH="$(PATH)" autoreconf -fi )

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-threads=posix
CONFIGURE_OPTIONS += --enable-install-gpg-error-config

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/xopen/xcu4
