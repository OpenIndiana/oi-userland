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
# Copyright 2024 Geoffrey Weiss
#

BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		appstream-glib
COMPONENT_VERSION=	0.8.3
COMPONENT_SUMMARY=	This library provides objects and helper methods to help reading and writing AppStream metadata. 
COMPONENT_SRC=		appstream-glib-appstream_glib_0_8_3
COMPONENT_ARCHIVE=	appstream_glib_0_8_3.tar.gz
COMPONENT_PROJECT_URL=	appstream
COMPONENT_ARCHIVE_URL=	https://github.com/hughsie/appstream-glib/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:15ad7690b0132d883bd066699a7b55f6cef4c0f266d18d781ce5d8112fb4ee63
COMPONENT_FMRI=		library/appstream-glib
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += -Drpm=false

# get rid of the timestamps from the test results
COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9]*[0-9].[0-9][0-9]s//" '

# Build dependencies
REQUIRED_PACKAGES += developer/gperf

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libyaml
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += web/curl
