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
# Copyright 2016 Alexander Pyhalov
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtk-vnc
HUMAN_VERSION=		1.4.0
COMPONENT_SUMMARY=	A VNC client viewer widget for GTK
COMPONENT_ARCHIVE_HASH=	sha256:1be64c4e4760c52b3ec33067290d1efa40ad4cecab6c673813804e3c559d9683
COMPONENT_FMRI=		library/desktop/gtk-vnc
COMPONENT_CLASSIFICATION= Development/GNOME and GTK+
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE=	COPYING.LIB

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
