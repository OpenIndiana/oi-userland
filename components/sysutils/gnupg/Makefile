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
# Copyright (c) 2013, Colin Ellis. All rights reserved.
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2021, Nona Hansel
# Copyright (c) 2021, 2024 Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gnupg
COMPONENT_VERSION=      2.4.7
COMPONENT_SUMMARY=      GNU Privacy Guard
COMPONENT_DESCRIPTION=	A complete and free implementation of the OpenPGP Standard as defined by RFC4880
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://gnupg.org/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:7b24706e4da7e0e3b06ca068231027401f238102c41c909631349dcc3b85eb46
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/ftp/gcrypt/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         crypto/gnupg
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=      GPLv3, GPLv2, LGPLv3, LGPLv2.1, Creative Commons 1.0, others

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += -I/usr/include/openldap

# If we pass -lc, -mt won't link with -lthread
# (which is what it does by default, and we don't
# want that, because we use POSIX threads).
LDFLAGS += -lc -z defs -lsocket -lnsl
LD_OPTIONS += -z defs

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += LDFLAGS="$(LDFLAGS)"
CONFIGURE_ENV += INSTALL="$(INSTALL)"
CONFIGURE_ENV += LDAPLIBS="-lldap-2.6 -llber-2.6"

CONFIGURE_OPTIONS += --libexecdir=$(USRBINDIR)
CONFIGURE_OPTIONS += --datadir=$(CONFIGURE_PREFIX)/share
CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --enable-largefile
CONFIGURE_OPTIONS += --disable-selinux-support
CONFIGURE_OPTIONS += --disable-libdns
CONFIGURE_OPTIONS += --with-pinentry-pgm=$(CONFIGURE_PREFIX)/libexec/pinentry
CONFIGURE_OPTIONS += --with-gpg-error-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-libassuan-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-ksba-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-libiconv-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-libintl-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-zlib=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-bzip2=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-readline=$(CONFIGURE_PREFIX)

COMPONENT_POST_INSTALL_ACTION += \
	( cd $(PROTOUSRSHARELOCALEDIR) ; \
	    $(CP) -R 'en@boldquot' en ) ;

# We do not want the info index file
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/info/dir ;

# Testing fails without HOME set
COMPONENT_TEST_ENV += HOME=/tmp

COMPONENT_TEST_TRANSFORMS += "-e '/Failed tests/p'"
COMPONENT_TEST_TRANSFORMS += "-e '/tests run/p'"
COMPONENT_TEST_TRANSFORMS += "-e '/test passed/p'"
COMPONENT_TEST_TRANSFORMS += "-e '/tests passed/p'"
COMPONENT_TEST_TRANSFORMS += "-e '/====/p'"

# Missing dependencies for pinentry
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += security/pinentry

# Auto-generated dependencies
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/npth
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/libassuan
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += library/security/libksba
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
