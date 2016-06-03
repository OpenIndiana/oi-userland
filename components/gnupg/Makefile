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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnupg
COMPONENT_VERSION=	2.0.29
COMPONENT_PROJECT_URL=	http://www.gnupg.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:68ed6b386ba78425b05a60e8ee22785ff0fef190bdc6f1c612f19a58819d4ac9
COMPONENT_ARCHIVE_URL=	ftp://ftp.gnupg.org/gcrypt/gnupg/$(COMPONENT_ARCHIVE)

TPNO=			26269

include $(WS_MAKE_RULES)/common.mk

# Enable C99 mode + -Xc for its additional warnings.
studio_C99MODE = -Xc $(studio_C99_ENABLE)

# -xinline=%auto -- we like inlining where appropriate
CFLAGS += -xinline=%auto

# -xbuiltin=%none -- builtins have been known to be buggy
CFLAGS += -xbuiltin=%none

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += $(XPG6MODE)
CFLAGS += $(CPP_POSIX)
CFLAGS += $(CPP_C99_EXTENDED_MATH)
CFLAGS += $(studio_PIC)

# If we pass -lc, -mt won't link with -lthread
# (which is what it does by default, and we don't
# want that, because we use POSIX threads).
LDFLAGS += -lc $(LD_Z_DEFS)
LD_OPTIONS += $(LD_Z_DEFS)

COMPONENT_TEST_TRANSFORMS += \
     '-e "/libtool/d"' \
     '-e "/-m32/d"' \
     '-e "/-m64/d"' \
     '-e "/ld: warning/d"' \
     '-e "/warning/d"' \
     '-e "/Generat/d"' \
     '-e "/Creat/d"' \
     '-e "/Compos/d"' \
     '-e "/Writ/d"' \
     '-e "/Read/d"' \
     '-e "/Home/d"' \
     '-e "/from/d"' \
     '-e "/--run/d"' \
     '-e "/rm -f/d"' \
     '-e "/Nothing/d"' \
     '-e "/Leaving/d"' \
     '-e "/Entering/d"' \
     '-e "/Making/d"' \
     '-e "/Known envvars/d"' \
     '-e "/make/d"' \
     '-e "s/[0-9]\{1,\}\.[0-9]\{1,\} s, //g"' \
     '-e "s^[0-9]\{1,\} kB/s^^g"'  \
     '-e "s^[0-9]\{1,\}  kB/s^^g"'  \
     '-e "s^[0-9]\{1,\}\.[0-9]\{1,\}  MB/s^^g"' \
     '-e "s^[0-9]\{1,\}\.[0-9]\{1,\} MB/s^^g"' \
     '-e "s/([0-9]\{1,\} B)//g"' \
     '-e "s/([0-9]\{1,\}  B)//g"' \
     '-e "s/copied,/copied/g"'  \
     '-e "s/ \{1,\}copied/ copied/g"'  \
     '-e "s/copied $$/copied/g"'  \
     '-e "s/copied [0-9]\{1,\}\./copied/g"'

CONFIGURE_ENV +=	INSTALL="$(INSTALL)"

# Without this GnuPG's ./configure will complain that we're not using
# GNU make. But we are.
CONFIGURE_ENV +=	MAKE="$(GMAKE)"

CONFIGURE_OPTIONS  +=		--localstatedir=$(VARDIR)
CONFIGURE_OPTIONS  +=		--libexecdir=$(USRBINDIR)
CONFIGURE_OPTIONS  +=		--datadir=$(CONFIGURE_PREFIX)/share
CONFIGURE_OPTIONS  +=		--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-nls
CONFIGURE_OPTIONS  +=		--enable-largefile
CONFIGURE_OPTIONS  +=		--disable-selinux-support
CONFIGURE_OPTIONS  +=		--with-pinentry-pgm=$(CONFIGURE_PREFIX)/lib/pinentry
CONFIGURE_OPTIONS  +=		--with-gpg-error-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-libassuan-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-ksba-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-pth-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-libcurl=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-libiconv-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-libintl-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-zlib=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-bzip2=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-readline=$(CONFIGURE_PREFIX)

LIBKSBA_MANIFEST = 	manifest-$(MACH)-libksba.depend
LIBASSUAN_MANIFEST =	manifest-$(MACH)-libassuan.depend
GPGME_MANIFEST =	manifest-$(MACH)-gpgme.depend
PINENTRY_MANIFEST =	manifest-$(MACH)-pinentry.depend

# Work around pkgdepend bug which doesn't resolve dependencies from
# the local workspace repo. Fortunately we only have to do this once.
DEPENDED +=	$(WS_TOP)/components/libksba/build/$(LIBKSBA_MANIFEST)
DEPENDED +=	$(WS_TOP)/components/libassuan/build/$(LIBASSUAN_MANIFEST)
DEPENDED +=	$(WS_TOP)/components/gpgme/build/$(GPGME_MANIFEST)
DEPENDED +=	$(WS_TOP)/components/pinentry/build/$(PINENTRY_MANIFEST)

PKG_PROTO_DIRS += $(WS_TOP)/components/libksba
PKG_PROTO_DIRS += $(WS_TOP)/components/libassuan
PKG_PROTO_DIRS += $(WS_TOP)/components/gpgme
PKG_PROTO_DIRS += $(WS_TOP)/components/pinentry

MAN8LIST = addgnupghome applygnupgdefaults

COMPONENT_POST_INSTALL_ACTION += \
	( cd $(PROTOUSRSHARELOCALEDIR) ; \
	    $(CP) -R 'en@boldquot' en )

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/pth
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/security/libassuan
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += library/security/libksba
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += security/pinentry
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/library/usb/libusb
REQUIRED_PACKAGES += system/network/ldap/openldap
REQUIRED_PACKAGES += web/curl
