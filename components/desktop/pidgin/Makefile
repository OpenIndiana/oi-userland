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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pidgin
COMPONENT_VERSION=	2.11.0
COMPONENT_PROJECT_URL=	http://www.pidgin.im
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:f72613440586da3bdba6d58e718dce1b2c310adf8946de66d8077823e57b3333
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

TPNO=			30500

# Cyrus SASL is S12-only (at least for evaluation builds).
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Need to pick up the Studio compiler as some Makefiles just use "cc".
# Need to pick up the GNU version of xgettext.
PATH=$(dir $(CC)):$(SPRO_VROOT)/bin:$(GNUBIN):$(USRBINDIR)

CFLAGS +=		-DG_IMPLEMENT_INLINES -DG_HAVE_ISO_VARARGS

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; \
	glib-gettextize -f ; \
	libtoolize --force ; \
	intltoolize --force --copy --automake ; \
	aclocal -I . ; \
	autoheader ; \
	automake -a -c -f ; \
	autoconf )

# Needed to get libpurple to link properly.
LIBS += -lresolv
CONFIGURE_ENV +=	LIBS="$(LIBS)"

CONFIGURE_ENV += "ac_cv_path_perlpath=$(PERL)"

CONFIGURE_OPTIONS +=	--enable-cyrus-sasl
CONFIGURE_OPTIONS +=	--enable-nss
CONFIGURE_OPTIONS +=	--with-nspr-includes=/usr/include/mps
CONFIGURE_OPTIONS +=	--with-nspr-libs=/usr/lib/mps/64
CONFIGURE_OPTIONS +=	--with-nss-includes=/usr/include/mps
CONFIGURE_OPTIONS +=	--with-nss-libs=/usr/lib/mps/64
CONFIGURE_OPTIONS +=	--disable-gnutls
CONFIGURE_OPTIONS +=	--enable-gnome-keyring
CONFIGURE_OPTIONS +=	--disable-gevolution
CONFIGURE_OPTIONS +=	--enable-cap
CONFIGURE_OPTIONS +=	--disable-meanwhile
CONFIGURE_OPTIONS +=	--disable-nm
CONFIGURE_OPTIONS +=	--enable-consoleui
CONFIGURE_OPTIONS +=	--with-ncurses-headers=/usr/include/ncurses
CONFIGURE_OPTIONS +=	--disable-vv
# 23200148 undo this once 23169155 Move developer/gnome/gettext to Userland
CONFIGURE_OPTIONS +=	INTLTOOL_MERGE="$(PERL) /usr/bin/intltool-merge"

# We have two implementations of libcurses in Solaris. finch needs to use the
# ncurses one. The curses implementations in turn, use libpanel, but the
# ncurses one is under /usr/gnu/lib. To make sure that it correctly uses that
# one, and not the one under /usr/lib, we need to remove all occurences of
# -L/usr/lib/$(MACH64), -L/usr/lib, -L/lib/$(MACH64) and -L/lib from all
# Makefiles.
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(@D) ; \
	mlist=`/usr/bin/find . -name 'Makefile'` ; \
	echo $$mlist ; \
	for f in $$mlist ; do \
		$(GSED) -i \
			-e 's|-L/usr/lib/$(MACH64) ||g' \
			-e 's|-L/usr/lib ||g' \
			-e 's|-L/lib/$(MACH64) ||g' \
			-e 's|-L/lib ||g' \
			$$f ; \
        done)

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS +=	V=1

# Prevent build problems with package_revision.h with "hg id ..." in the main
# pidgin Makefile, if the user has color.mode=terminfo in their ~/.hgrc file.
COMPONENT_BUILD_ARGS += HGPLAIN=
COMPONENT_BUILD_ARGS += HGRCPATH=/dev/null

REQUIRED_PACKAGES += communication/im/pidgin-gnome-keyring
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gstreamer-1
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-good
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtkspell
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/perl-5/xml-parser
REQUIRED_PACKAGES += library/python/dbus-python-27
# Remove once all build machines are upgraded to dbus-python-27:
REQUIRED_PACKAGES += library/python/python-dbus-27
REQUIRED_PACKAGES += library/security/nss
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += runtime/tk-8
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/security/libsasl2
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxscrnsaver
