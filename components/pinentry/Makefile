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

PATH = $(GNUBIN):$(USRBINDIR)

COMPONENT_NAME=		pinentry
COMPONENT_VERSION=	0.9.7
COMPONENT_PROJECT_URL=	http://www.gnupg.org/related_software/pinentry/
COMPONENT_ARCHIVE=     $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:6398208394972bbf897c3325780195584682a0d0c164ca5a0da35b93b1e4e7b2
COMPONENT_ARCHIVE_URL=	ftp://ftp.gnupg.org/gcrypt/pinentry/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnupg

TPNO=			26271

INSTALL_TARGET=
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL = 0

# Enable C99 mode + -Xc for its additional warnings.
studio_C99MODE = -Xc $(studio_C99_ENABLE)

# suppress warning: "-features=typeof ignored when used with -Xc"
CFLAGS.studio += -features=no%typeof

# -xinline=%auto -- we like inlining where appropriate
CFLAGS.studio += -xinline=%auto

# -xbuiltin=%none -- builtins have been known to be buggy
CFLAGS.studio += -xbuiltin=%none

# void function cannot return value, unless it's GNU C
CFLAGS.studio += -features=extinl,extensions

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += $(XPG6MODE)
CFLAGS += $(CPP_POSIX)
CFLAGS += $(CPP_C99_EXTENDED_MATH)
CFLAGS += $(CC_PIC)

# prevent libtool from removing these
ifeq ($(OS_VERSION),5.11)
LDFLAGS += -lsocket -lnsl
LIBS += -lsocket -lnsl
endif

LDFLAGS += -lpkcs11
LIBS += -lpkcs11


CONFIGURE_ENV +=	INSTALL="$(INSTALL)"
CONFIGURE_ENV +=	LIBS="$(LIBS)"

CONFIGURE_OPTIONS  +=		--localstatedir=$(VARDIR)
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-pinentry-curses
CONFIGURE_OPTIONS  +=		--enable-pinentry-gtk2
CONFIGURE_OPTIONS  +=		--disable-pinentry-qt
CONFIGURE_OPTIONS  +=		--disable-ncurses
CONFIGURE_OPTIONS  +=		--disable-libsecret

install: $(INSTALL_64)
	$(MKDIR) $(PROTOUSRLIBDIR)
	if test -f $(PROTOUSRBINDIR)/pinentry-curses ; then \
	$(MV) $(PROTOUSRBINDIR)/pinentry-curses $(PROTOUSRLIBDIR)/ ; fi
	if test -f $(PROTOUSRBINDIR)/pinentry-gtk-2 ; then \
	$(MV) $(PROTOUSRBINDIR)/pinentry-gtk-2 $(PROTOUSRLIBDIR)/ ; fi
	cd $(PROTOUSRLIBDIR) && ln -sf pinentry-gtk-2 pinentry

REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/security/libassuan
REQUIRED_PACKAGES += library/security/libgpg-error
