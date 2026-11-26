#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2026 isoriano1968
#

# gnome-menus 3.36.0 (libgnome-menu-3, the freedesktop menu library that
# gnome-panel's menus use), as in Solaris 11.4 (solaris-userland
# components/gnome/gnome-menus @9d7a655): patches/01-gio-unix-gir.patch is
# upstream commit fe1eca74 (GDesktopAppInfo lives in GioUnix-2.0 since GLib
# 2.80; https://gitlab.gnome.org/GNOME/gnome-menus/-/issues/25).
# FMRI gnome/gnome-menus as OpenIndiana's obsolete GNOME 2 package of the
# same library (2.30.5); Solaris calls it library/gnome/gnome-menus.

BUILD_BITS=		64
BUILD_STYLE=		configure

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-menus
HUMAN_VERSION=		3.36.0
COMPONENT_SUMMARY=	The GNOME Menu Library
COMPONENT_ARCHIVE_HASH=	\
	sha256:d9348f38bde956fc32753b28c1cde19c175bfdbf1f4d5b06003b3aa09153bb1f
COMPONENT_FMRI=		gnome/gnome-menus
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-2.0-or-later AND GPL-2.0-or-later
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# illumos: the strict standard mode hides stack_t etc. that system headers
# (libgtop's procfs, kvm) need; -D_REENTRANT for GLib's per-thread errno
CFLAGS +=		-D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS -D_REENTRANT

# the patch changes configure.ac and libmenu/Makefile.am
COMPONENT_PREP_ACTION +=	(cd $(@D) && PATH="$(PATH)" $(AUTORECONF) -fi) ;

CONFIGURE_ENV +=	PATH="$(GNUBIN):$(PATH)"
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-introspection
# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
