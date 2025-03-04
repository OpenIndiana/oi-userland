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

COMPONENT_NAME=			libmediaart
HUMAN_VERSION=			1.9.7
COMPONENT_SUMMARY=		Library tasked with managing, extracting and handling media art caches
COMPONENT_ARCHIVE_HASH=		sha256:2b43dd9f54f0d8d0b89e2addb83341ab06d7b98cb1b2e704383584af9c560f6b
COMPONENT_FMRI=			library/gnome/libmediaart
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE=		COPYING.LESSER

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# Manually added build dependencies
REQUIRED_PACKAGES += developer/vala

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
