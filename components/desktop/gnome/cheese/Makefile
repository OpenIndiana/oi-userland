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

BUILD_STYLE=		meson

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cheese
HUMAN_VERSION=		44.1
COMPONENT_SUMMARY=	Cheese - take photos and videos with your webcam
COMPONENT_ARCHIVE_HASH=	\
	sha256:5f2185c4c99e54ddf2b8baf60c82819950e54952e132e8639875f3edcbf8f68e
COMPONENT_FMRI=		media/cheese
COMPONENT_CLASSIFICATION=	Applications/Sound and Video
COMPONENT_LICENSE=	GPL-2.0-or-later
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is expected
PATH=			$(PATH.gnu)

# gcc 14 makes these errors (libcheese and Vala's generated C)
CFLAGS +=		-Wno-error=incompatible-pointer-types -Wno-error=int-conversion

CONFIGURE_OPTIONS +=	-Dgtk_doc=false

# cheese is partly written in Vala
REQUIRED_PACKAGES += developer/vala
# gstreamer-plugins-bad-1.0 (meson.build requires it)
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/bad

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/clutter/clutter-gst
REQUIRED_PACKAGES += library/desktop/clutter/clutter-gtk
REQUIRED_PACKAGES += library/desktop/cogl
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gnome-desktop
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
