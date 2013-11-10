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
include ../../make-rules/shared-macros.mk

PATH = /usr/gnu/bin:/usr/bin

COMPONENT_NAME=		pinentry
COMPONENT_VERSION=	0.8.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.gnupg.org/related_software/pinentry/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:568b0b09b50b2388a4f94d704d5bcb28718ecd4654ed1acc43ab1f97d921a0ad
COMPONENT_ARCHIVE_URL=	ftp://ftp.gnupg.org/gcrypt/pinentry/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnupg

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

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

CONFIGURE_OPTIONS  +=		--localstatedir=/var
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-pinentry-curses
CONFIGURE_OPTIONS  +=		--enable-pinentry-gtk2
CONFIGURE_OPTIONS  +=		--disable-glibtest
CONFIGURE_OPTIONS  +=		--disable-gtktest
CONFIGURE_OPTIONS  +=		--enable-threading
CONFIGURE_OPTIONS  +=		--disable-pinentry-gtk
CONFIGURE_OPTIONS  +=		--disable-pinentry-qt
CONFIGURE_OPTIONS  +=		--disable-ncurses

build: $(BUILD_32)

install: $(INSTALL_32)
	$(MKDIR) $(PROTOUSRLIBDIR)
	if test -f $(PROTOUSRBINDIR)/pinentry-curses ; then \
	$(MV) $(PROTOUSRBINDIR)/pinentry-curses $(PROTOUSRLIBDIR)/ ; fi
	if test -f $(PROTOUSRBINDIR)/pinentry-gtk-2 ; then \
	$(MV) $(PROTOUSRBINDIR)/pinentry-gtk-2 $(PROTOUSRLIBDIR)/ ; fi
	cd $(PROTOUSRLIBDIR) && ln -sf pinentry-gtk-2 pinentry

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

