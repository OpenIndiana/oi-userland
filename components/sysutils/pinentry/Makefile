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
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk


COMPONENT_NAME=		pinentry
COMPONENT_VERSION=	1.1.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.gnupg.org/related_software/pinentry/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:68076686fa724a290ea49cdf0d1c0c1500907d1b759a3bcbfbec0293e8f56570
COMPONENT_ARCHIVE_URL=	https://www.gnupg.org/ftp/gcrypt/pinentry/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		security/pinentry

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

PATCH_LEVEL = 0

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += $(XPG6MODE)
CFLAGS += $(CPP_POSIX)
CFLAGS += $(CPP_C99_EXTENDED_MATH)
CFLAGS += $(gcc_C99_ENABLE)

# prevent libtool from removing these
LDFLAGS += -lsocket -lnsl -lpkcs11
LIBS = -lsocket -lnsl -lpkcs11

CONFIGURE_ENV +=	INSTALL="$(INSTALL)"
CONFIGURE_ENV +=	LIBS="$(LIBS)"
# Following line is required if FLTK pinentry is to be shipped
# CONFIGURE_ENV +=	FLTK_CONFIG="$(USRBINDIR.$(BITS))/fltk-config"

CONFIGURE_OPTIONS  +=		--localstatedir=/var
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-pinentry-curses
CONFIGURE_OPTIONS  +=		--enable-pinentry-gtk2
CONFIGURE_OPTIONS  +=		--disable-pinentry-qt
CONFIGURE_OPTIONS  +=		--disable-ncurses
CONFIGURE_OPTIONS  +=		--disable-pinentry-fltk

build: $(BUILD_64)

install: $(INSTALL_64)
	$(MKDIR) $(PROTOUSRLIBDIR)
	if test -f $(PROTOUSRBINDIR)/pinentry-curses ; then \
	$(MV) $(PROTOUSRBINDIR)/pinentry-curses $(PROTOUSRLIBDIR)/ ; fi
	if test -f $(PROTOUSRBINDIR)/pinentry-gtk-2 ; then \
	$(MV) $(PROTOUSRBINDIR)/pinentry-gtk-2 $(PROTOUSRLIBDIR)/ ; fi
	cd $(PROTOUSRLIBDIR) && ln -sf pinentry-gtk-2 pinentry

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/security/libassuan
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += system/library
