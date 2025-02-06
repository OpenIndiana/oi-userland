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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			totem-pl-parser
HUMAN_VERSION=			3.26.6
COMPONENT_SUMMARY=		Simple GObject-based library to parse a host of playlist formats
COMPONENT_ARCHIVE_HASH=		sha256:c0df0f68d5cf9d7da43c81c7f13f11158358368f98c22d47722f3bd04bd3ac1c
COMPONENT_FMRI=			library/media-player/totem-pl-parser
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPL-2.0-only
COMPONENT_LICENSE_FILE=		COPYING.LIB

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# Testing fails with uchardet because it detects IBM865 codepage but our iconv
# does not support that.
# See also https://www.freedesktop.org/wiki/Software/uchardet
CONFIGURE_OPTIONS += -Denable-uchardet=no

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
