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

BUILD_BITS =            32_and_64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gst-plugins-good
COMPONENT_VERSION=	1.4.5
COMPONENT_PROJECT_URL=	http://gstreamer.freedesktop.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:79b1b5f3f7bcaa8a615202eb5e176121eeb8336960f70687e536ad78dbc7e641
COMPONENT_ARCHIVE_URL=	http://gstreamer.freedesktop.org/src/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/multimedia

TPNO=			25637

# Hook up tests after build servers are installed with dependencies
TEST_TARGET= $(SKIP_TEST)

# Only build for 2.7 for now as we need 32-bit and 64-bit support; all of the
# GNOME and desktop components must be built for Python 2.7 for now.
PYTHON_VERSIONS= 2.7

# Needs gobject-introspection, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -std=c++11

# configure script uses AC_CHECK_PROG erroneously; AC_CHECK_PROG looks for a
# program in $PATH by default, and fails even if you provide an absolute path
# to the command (no idea why); override the failed check.
CONFIGURE_ENV += ac_cv_prog_HAVE_CXX=yes

# No need for firewire support.
CONFIGURE_OPTIONS += --disable-dv1394
# Linux only; requires ALSA.
CONFIGURE_OPTIONS += --disable-monoscope
CONFIGURE_OPTIONS += --disable-static
# sunaudio no longer builds; interfaces used in gstreamer are gone (mixer.h).
CONFIGURE_OPTIONS += --disable-sunaudio
CONFIGURE_OPTIONS += --enable-bz2
CONFIGURE_OPTIONS += --enable-cairo
CONFIGURE_OPTIONS += --enable-jpeg
CONFIGURE_OPTIONS += --enable-libpng
CONFIGURE_OPTIONS += --enable-oss
CONFIGURE_OPTIONS += --enable-oss4
CONFIGURE_OPTIONS += --enable-pulse
CONFIGURE_OPTIONS += --enable-soup
CONFIGURE_OPTIONS += --enable-speex
CONFIGURE_OPTIONS += --enable-taglib
CONFIGURE_OPTIONS += --enable-vpx
CONFIGURE_OPTIONS += --enable-x
CONFIGURE_OPTIONS += --enable-xshm
CONFIGURE_OPTIONS += --enable-zlib
CONFIGURE_OPTIONS += --with-x

# Ensure system-default python is not used.
CONFIGURE_ENV += PYTHON="$(PYTHON.2.7)"

# Ensure Python modules are installed into vendor package directories.
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)

# Required due to patches.
COMPONENT_PREP_ACTION += ( cd $(@D) ; NOCONFIGURE=1 $(CONFIG_SHELL) autogen.sh );

REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += codec/libogg
REQUIRED_PACKAGES += codec/libtheora
REQUIRED_PACKAGES += codec/libvorbis
REQUIRED_PACKAGES += codec/libvpx
REQUIRED_PACKAGES += codec/speex
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += library/aalib
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/audio/taglib
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gstreamer-1
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-base
REQUIRED_PACKAGES += library/desktop/libvisual
REQUIRED_PACKAGES += library/desktop/orc
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxv
