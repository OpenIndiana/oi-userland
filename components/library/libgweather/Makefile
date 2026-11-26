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

# libgweather 4.4.4 as in Solaris 11.4 (solaris-userland components/gnome/
# libgweather @9d7a655), with its alloca patch (upstream MR 326).

BUILD_BITS=		64
BUILD_STYLE=		meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgweather
HUMAN_VERSION=		4.4.4
COMPONENT_SUMMARY=	libgweather - GNOME weather and location library
COMPONENT_ARCHIVE_HASH=	\
	sha256:7017677753cdf7d1fdc355e4bfcdb1eba8369793a8df24d241427a939cbf4283
COMPONENT_FMRI=		library/desktop/libgweather
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	GPL-2.0-or-later
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

CPPFLAGS +=		-D__EXTENSIONS__

CONFIGURE_OPTIONS +=	-Dgtk_doc=false
CONFIGURE_OPTIONS +=	-Dtests=false
CONFIGURE_OPTIONS +=	-Dsoup2=false
CONFIGURE_OPTIONS +=	-Denable_vala=false
CONFIGURE_OPTIONS +=	-Dzoneinfo_dir=/usr/share/lib/zoneinfo

CONFIGURE_ENV +=	PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/geocode-glib-2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/libsoup3
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
