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

# geocode-glib 3.26.4 built against libsoup 3 (-Dsoup2=false): API
# geocode-glib-2.0, needed by libgweather 4.  OI's library/desktop/geocode-glib
# is the libsoup 2 build (geocode-glib-1.0).  Both install side by side: this
# package ships only the -2.0 library, headers, pkg-config and GIR files; the
# icons it shares with the 1.0 build come from OI's package, which this one
# depends on.  (Solaris builds only the soup3 variant.)

BUILD_BITS=		64
BUILD_STYLE=		meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		geocode-glib
HUMAN_VERSION=		3.26.4
COMPONENT_SUMMARY=	geocode-glib (libsoup 3 API 2.0) - geocoding and reverse geocoding
COMPONENT_ARCHIVE_HASH=	\
	sha256:2d9a6826d158470449a173871221596da0f83ebdcff98b90c7049089056a37aa
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/3.26/$(COMPONENT_NAME)-$(HUMAN_VERSION).tar.xz
COMPONENT_FMRI=		library/desktop/geocode-glib-2
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-2.0-or-later
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# per-thread errno on illumos (GLib programs are threaded)
CFLAGS +=		-D_REENTRANT

CONFIGURE_OPTIONS +=	--libexecdir=$(USRLIBEXECDIR)
CONFIGURE_OPTIONS +=	-Dsoup2=false
CONFIGURE_OPTIONS +=	-Denable-gtk-doc=false
CONFIGURE_OPTIONS +=	-Denable-installed-tests=false
CONFIGURE_OPTIONS +=	-Denable-introspection=true

CONFIGURE_ENV +=	PATH="$(GNUBIN):$(PATH)"

# Shared with OI's geocode-glib (1.0) package: leave them to it.
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) -r $(PROTO_DIR)/usr/share/icons $(PROTO_DIR)/usr/share/gtk-doc ;

REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/geocode-glib
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup3
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
