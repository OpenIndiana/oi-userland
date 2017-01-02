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

#
# This file sets up the default options and base requirements for GNOME
# components.
#
# Most cmake-based components require intltools.
include $(WS_MAKE_RULES)/intltool.mk
# cmake components don't generally use autoconf.
include $(WS_MAKE_RULES)/justmake.mk

# Ensure correct version of libraries are linked to.
LDFLAGS += "$(CC_BITS)"

# This component uses cmake to generate Makefiles and so has no configure
CMAKE = $(shell which cmake)
CMAKE_BUILD_TYPE ?= RelWithDebInfo

# Layout configuration.
CMAKE_PREFIX ?= $(USRDIR)

CMAKE_OPTIONS += -DCMAKE_CXX_COMPILER="$(CXX)"
CMAKE_OPTIONS += -DCMAKE_CXX_FLAGS="$(CXXFLAGS)"
CMAKE_OPTIONS += -DCMAKE_C_COMPILER="$(CC)"
CMAKE_OPTIONS += -DCMAKE_C_FLAGS="$(CFLAGS)"
CMAKE_OPTIONS += -DCMAKE_EXE_LINKER_FLAGS="$(LDFLAGS)"

# Must start install paths with a leading '/' or files will be installed into
# wrong location!
CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX="$(CMAKE_PREFIX)"
CMAKE_OPTIONS += -DCMAKE_MODULE_LINKER_FLAGS="$(LDFLAGS)"
CMAKE_OPTIONS += -DCMAKE_SHARED_LINKER_FLAGS="$(LDFLAGS)"
CMAKE_OPTIONS += -DGETTEXT_MSGFMT_EXECUTABLE="$(GNUBIN)/msgfmt"
CMAKE_OPTIONS += -DBIN_INSTALL_DIR="$(USRBIN)"
CMAKE_OPTIONS += -DEXEC_INSTALL_DIR="$(USRBIN)"

# Some components use LIB_INSTALL_DIR, as-is, others forcibly ignore it and set
# based on CMAKE_INSTALL_PREFIX.  Those usually instead offer a LIB_SUFFIX
# variable that we can generally use to accomplish the same result.  Setting
# them both shouldn't harm anything.
CMAKE_OPTIONS += -DLIB_INSTALL_DIR="$(USRLIB)"
CMAKE_OPTIONS.64 += -DLIB_SUFFIX="/$(MACH64)"
CMAKE_OPTIONS += -DLIBEXEC_INSTALL_DIR="$(USRLIB)"

# Required to ensure expected defines are set; also, ensures project's
# optimisation level set appropriately.
CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE)

CMAKE_OPTIONS += $(CMAKE_OPTIONS.$(BITS))

COMPONENT_PRE_BUILD_ACTION += cd $(@D);
COMPONENT_PRE_BUILD_ACTION += echo Running cmake with $(CMAKE_OPTIONS);
COMPONENT_PRE_BUILD_ACTION += $(CMAKE) . $(CMAKE_OPTIONS);

# Ensure cmake finds the matching 32/64-bit version of dependencies.
COMPONENT_BUILD_ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH)"

REQUIRED_PACKAGES += developer/build/cmake
REQUIRED_PACKAGES += developer/build/pkg-config
REQUIRED_PACKAGES += developer/gnu-binutils
REQUIRED_PACKAGES += developer/intltool
REQUIRED_PACKAGES += library/gnome/gnome-common
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/linker
# Most cmake-based components expect GNU versions of these.
REQUIRED_PACKAGES += text/gawk
REQUIRED_PACKAGES += text/gnu-gettext
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += text/gnu-sed
