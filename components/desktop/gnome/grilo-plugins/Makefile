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
# Copyright 2025 Marcel Telka
#

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=			grilo-plugins
HUMAN_VERSION=			0.3.16
COMPONENT_SUMMARY=		Collection of plugins for Grilo implementing Grilo's API for various multimedia content providers
COMPONENT_ARCHIVE_HASH=		sha256:fe6f4dbe586c6b8ba2406394e202f22d009d642a96eb3a54f32f6a21d084cdcb
COMPONENT_FMRI=			library/gnome/grilo-plugins
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH = $(PATH.gnu)

# Our GStreamer does not have chromaprint support because we do not have
# libchromaprint and so the chromaprint support in grilo-plugins would be
# useless.
CONFIGURE_OPTIONS += -Denable-chromaprint=no
# thetvdb tests fails.  Since we do not have any consumer for thetvdb we simply
# disable it.
CONFIGURE_OPTIONS += -Denable-thetvdb=no

# needed for bind(3socket)
LDFLAGS += -lsocket -lnsl

# Auto-generated dependencies
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/grilo
REQUIRED_PACKAGES += library/gnome/libgom
REQUIRED_PACKAGES += library/gnome/libmediaart
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/liboauth
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/media-player/totem-pl-parser
REQUIRED_PACKAGES += runtime/lua-54
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/network/avahi
