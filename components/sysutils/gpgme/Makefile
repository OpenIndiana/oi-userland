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

BUILD_BITS = 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gpgme
COMPONENT_VERSION=	1.21.0
COMPONENT_SUMMARY=	GnuPG Made Easy
COMPONENT_DESCRIPTION=	A library designed to make access to GnuPG easier for applications
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.gnupg.org/related_software/gpgme/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:416e174e165734d84806253f8c96bda2993fd07f258c3aad5f053a6efd463e88
COMPONENT_ARCHIVE_URL=	ftp://ftp.gnupg.org/gcrypt/gpgme/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/security/gpgme
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	GPLv2,LGPLv2

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && PATH=$(PATH.gnu) autoreconf -fi )

PATH = $(PATH.gnu)

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += $(XPG6MODE)
CFLAGS += $(CPP_POSIX)
CFLAGS += $(CPP_C99_EXTENDED_MATH)
CFLAGS += $(gcc_C99_ENABLE)

CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"
CONFIGURE_ENV +=	INSTALL="$(INSTALL)"

CONFIGURE_OPTIONS  +=		--localstatedir=/var
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--with-gpg-error-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-libgpg-error-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--enable-largefile
CONFIGURE_OPTIONS  +=		--with-pth=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--enable-languages=cl
CONFIGURE_OPTIONS  +=		--enable-gpg-test
CONFIGURE_OPTIONS  +=		--enable-gpgsm-test
CONFIGURE_OPTIONS  +=		--enable-gpgconf-test
CONFIGURE_OPTIONS  +=		--with-gpg=$(USRBINDIR)/gpg
CONFIGURE_OPTIONS  +=		--with-gpgsm=$(USRBINDIR)/gpgsm
CONFIGURE_OPTIONS  +=		--with-gpgconf=$(USRBINDIR)/gpgconf
CONFIGURE_OPTIONS  +=		--with-pic

# Please see comments in patches/GNUPGHOME.patch
GNUPG_HOME_DIR = GNUPGHOME
GNUPG_HOME_LINK = LINK
COMPONENT_PRE_BUILD_ACTION += ( \
    set -x; \
    DEST="$(@D)/$(GNUPG_HOME_DIR)"; \
    LINK="$$(mktemp)"; \
    echo "$$LINK" | tee "$(@D)/$(GNUPG_HOME_LINK)"; \
    $(RM) "$$DEST" "$$LINK"; \
    $(MKDIR) "$$DEST"; \
    ln -s "$$DEST" "$$LINK"; \
);

COMPONENT_POST_BUILD_ACTION += ( \
    set -x; \
    LINK="$$(< "$(@D)/$(GNUPG_HOME_LINK)")"; \
    [ -z "$$LINK" ] || $(RM) "$$LINK"; \
);

COMPONENT_BUILD_ARGS += GNUPGHOME="$$(< "$(@D)/$(GNUPG_HOME_LINK)")"

# In the 'doc' directory CC_FOR_BUILD is used as a compiler. That does not
# respect our CFLAGS and CPPFLAGS so the PIC build breaks. This is a way to
# overcome it.
COMPONENT_BUILD_ARGS += CC_FOR_BUILD='$(CC) $(CONFIGURE_CPPFLAGS) $(CC_PIC_ENABLE)'

COMPONENT_PRE_TEST_ACTION = $(COMPONENT_PRE_BUILD_ACTION)
COMPONENT_POST_TEST_ACTION = $(COMPONENT_POST_BUILD_ACTION)
COMPONENT_TEST_ARGS += GNUPGHOME="$$(< "$(@D)/$(GNUPG_HOME_LINK)")"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/libassuan
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
