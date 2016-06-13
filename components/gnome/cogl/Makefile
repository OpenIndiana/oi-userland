#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            64_and_32
# Also, all components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cogl
COMPONENT_VERSION=	1.22.0
COMPONENT_PROJECT_URL=  https://developer.gnome.org/cogl/
COMPONENT_ARCHIVE_HASH=	\
	sha256:689dfb5d14fc1106e9d2ded0f7930dcf7265d0bc84fa846b4f03941633eeaa91
COMPONENT_BUGDB=        gnome/libraries

TPNO=			25267

# Needs gobject-introspection, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

# Enable tests once all dependencies are install on the build server
TEST_TARGET = $(SKIP_TEST)

include $(WS_MAKE_RULES)/gnome-component.mk

# Delete this when build servers are installed with an updated versions of
# gst-plugins-base
GST_BASE = $(WS_COMPONENTS)/desktop/gstreamer1/gst-plugins-base/build/prototype/$(MACH)
PKG_CONFIG_PATHS.32 += $(GST_BASE)/usr/lib/pkgconfig/
PKG_CONFIG_PATHS.64 += $(GST_BASE)/usr/lib/$(MACH64)/pkgconfig/
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
CPPFLAGS += -I$(GST_BASE)/usr/include/gstreamer-1.0
LD_OPTIONS.32 += -L $(GST_BASE)/usr/lib
LD_OPTIONS.64 += -L $(GST_BASE)/usr/lib/$(MACH64)
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

DEPENDED += $(WS_TOP)/components/desktop/gstreamer1/gst-plugins-base/build/manifest-$(MACH)-gst-plugins-base.depend

# Temporary until dependencies are all on build machines
REQUIRED_PACKAGES += $(shell $(GSED) -n 's/REQUIRED_PACKAGES +=//p' ../../desktop/gstreamer1/gst-plugins-base/Makefile)
# end Delete

CONFIGURE_OPTION += --disable-static
# Required for other components.
CONFIGURE_OPTIONS += --enable-glib
# Required for other components.
CONFIGURE_OPTIONS += --enable-cogl-pango
# Required for other components.
CONFIGURE_OPTIONS += --enable-cogl-gst
# Required for other components.
CONFIGURE_OPTIONS += --enable-cogl-path
# Required for other components.
CONFIGURE_OPTIONS += --enable-gdk-pixbuf
# Required for other components.
CONFIGURE_OPTIONS += --enable-gl
# Required for other components.
CONFIGURE_OPTIONS += --enable-glx
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-x

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gstreamer-1
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-base
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += service/opengl/ogl-select
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxrandr
