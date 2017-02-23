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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

# parfait is a bit unhappy (24796572)
export PARFAIT_BUILD=no

BUILD_BITS= 64
# For now, all things built for C++11 require gcc; the cmake files for this
# project already specify the required -std.
COMPILER= gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		webkitgtk
COMPONENT_VERSION=	2.8.4
COMPONENT_PROJECT_URL=	http://webkitgtk.org
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:30bd366bd970d4bac2f9ef5bff0fb935376bf91ea2aaa2a5183fe5fdbec20fbd
COMPONENT_ARCHIVE_URL=	http://webkitgtk.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/webkitgtk
COMPONENT_ANITYA_ID=	5355

TPNO=			25892

# Use project's own optimization flags instead.
gcc_OPT=

# Requires newer version of cairo, available in S12 but not 11.3,
# so do not publish.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

BUILD_STYLE= justmake
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS += -j4

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
PKG_CONFIG_PATHS.32 += $(PKG_CONFIG_PATH.32)/gnutls-3
PKG_CONFIG_PATHS.64 += $(PKG_CONFIG_PATH.64)/gnutls-3
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.32 += -L $(USRLIB.32)/gnutls-3 -R $(USRLIB.32)/gnutls-3
LD_OPTIONS.64 += -L $(USRLIB.64)/gnutls-3 -R $(USRLIB.64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

PKG_CONFIG_PATHS.32 += $(PKG_CONFIG_PATH.32)/libnotify-4
PKG_CONFIG_PATHS.64 += $(PKG_CONFIG_PATH.64)/libnotify-4
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.32 += -L $(USRLIB.32)/libnotify-4 -R $(USRLIB.32)/libnotify-4
LD_OPTIONS.64 += -L $(USRLIB.64)/libnotify-4 -R $(USRLIB.64)/libnotify-4
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

# Required to ensure expected defines are set; also, ensures project's
# optimisation level set appropriately.  Would prefer RelWithDebInfo, but that
# target is curently broken.
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DENABLE_MINIBROWSER=ON
CMAKE_OPTIONS += -DPORT=GTK

ifeq ($(MACH), sparc)
CMAKE_OPTIONS += -DENABLE_JIT=OFF
endif

# Need to figure out a way to use BUILD_STYLE = cmake and remove
# these duplicate entries here - 24375155
# This component uses cmake to generate Makefiles and so has no configure
CMAKE           = $(shell which cmake)
CMAKE_OPTIONS += -DCMAKE_CXX_COMPILER="$(CXX)"
CMAKE_OPTIONS += -DCMAKE_CXX_FLAGS="$(CXXFLAGS)"
CMAKE_OPTIONS += -DCMAKE_C_COMPILER="$(CC)"
CMAKE_OPTIONS += -DCMAKE_C_FLAGS="$(CFLAGS)"
CMAKE_OPTIONS += -DCMAKE_EXE_LINKER_FLAGS="$(LDFLAGS)"
# Must start install paths with a leading '/' or files will be installed into
# wrong location!
CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX="$(USRDIR)"
CMAKE_OPTIONS += -DCMAKE_MODULE_LINKER_FLAGS="$(LDFLAGS)"
CMAKE_OPTIONS += -DCMAKE_SHARED_LINKER_FLAGS="$(LDFLAGS)"
CMAKE_OPTIONS += -DGETTEXT_MSGFMT_EXECUTABLE="$(GNUBIN)/msgfmt"
CMAKE_OPTIONS += -DEXEC_INSTALL_DIR="$(USRBIN)"
CMAKE_OPTIONS += -DLIB_INSTALL_DIR="$(USRLIB)"
CMAKE_OPTIONS += -DLIBEXEC_INSTALL_DIR="$(USRLIB)"

# Tell g-ir-scanner not to cache results in homedir of user running the build
COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

# Expects GNU versions of utilities to be found in PATH (e.g. xgettext).
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

# Ensure cmake finds the matching 32/64-bit version of dependencies.
COMPONENT_BUILD_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

COMPONENT_PRE_BUILD_ACTION += cd $(@D);
COMPONENT_PRE_BUILD_ACTION += echo Running cmake with $(CMAKE_OPTIONS);
COMPONENT_PRE_BUILD_ACTION += $(ENV) $(COMPONENT_BUILD_ENV) $(CMAKE) . $(CMAKE_OPTIONS);

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/build/cmake
REQUIRED_PACKAGES += developer/build/gnu-make
REQUIRED_PACKAGES += developer/build/pkg-config
REQUIRED_PACKAGES += developer/gperf
REQUIRED_PACKAGES += developer/parser/bison
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += image/library/libwebp
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gstreamer-1
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-base
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/harfbuzz
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/gnome/libsecret
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/desktop/libnotify
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/ruby
REQUIRED_PACKAGES += service/opengl/ogl-select
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/mesa
