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
CARGO_VENDOR=		yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gst-plugins-rs
COMPONENT_VERSION=	0.15.4
COMPONENT_SUMMARY=	GStreamer Rust plugins: gtk4paintablesink
COMPONENT_PROJECT_URL=	https://gitlab.freedesktop.org/gstreamer/gst-plugins-rs
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:2c19ed8316695782b782135ba35601a78886e16f5197965aab66d26f477534ed
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/-/archive/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/audio/gstreamer/plugin/gtk4
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_LICENSE=	MPL-2.0
COMPONENT_LICENSE_FILE=	LICENSE-MPL-2.0

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# only the gtk4 plugin (gtk4paintablesink, for GTK 4 video players)
CONFIGURE_OPTIONS +=	-Dauto_features=disabled
CONFIGURE_OPTIONS +=	-Dgtk4=enabled

# cargo runs offline on the vendored crates
COMPONENT_BUILD_ENV +=	CARGO_NET_OFFLINE=true

# meson builds the plugin with cargo-c
REQUIRED_PACKAGES +=	developer/cargo-c
# meson.build reads the Cargo files with tomli (python3.9)
REQUIRED_PACKAGES +=	library/python/tomli-39
REQUIRED_PACKAGES +=	developer/lang/rustc

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/desktop/graphene
REQUIRED_PACKAGES += library/desktop/gtk4
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
