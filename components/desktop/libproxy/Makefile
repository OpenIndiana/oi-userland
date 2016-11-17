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
BUILD_BITS= 		32_and_64
COMPILER= 		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libproxy
COMPONENT_VERSION=	0.4.11.1
COMPONENT_PROJECT_URL=	https://code.google.com/p/libproxy
COMPONENT_SRC=		$(COMPONENT_NAME)-master
COMPONENT_ARCHIVE=	master.zip
COMPONENT_ARCHIVE_URL=	https://github.com/binarycrusader/$(COMPONENT_NAME)/archive/master.zip
COMPONENT_BUGDB=	library/libproxy

TPNO=			24459

BUILD_STYLE= 		cmake
include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -std=c++11

# Only compatible with Python 2.x.
PYTHON_VERSION=2.7
PYTHON_VERSIONS=2.7

# Our Perl 5.22 is 64-bit, so don't deliver Perl bindings for 32-bit build.
CMAKE_OPTIONS.32 = -DWITH_PERL=OFF
CMAKE_OPTIONS.64 = -DWITH_PERL=ON

CMAKE_OPTIONS += -DINCLUDE_INSTALL_DIR="$(USRINCDIR)/$(COMPONENT_NAME)"
CMAKE_OPTIONS += -DPERL_VENDORINSTALL=ON
CMAKE_OPTIONS += -DPYTHON_EXECUTABLE="$(PYTHON)"
CMAKE_OPTIONS += -DPYTHON_SITEPKG_DIR=$(PYTHON_LIB)
# Required for other components.
CMAKE_OPTIONS += -DWITH_GNOME3=ON
CMAKE_OPTIONS += -DWITH_PYTHON=ON
# Required for other components.
CMAKE_OPTIONS += -DWITH_VALA=ON
# Always build pacrunner as a module.
CMAKE_OPTIONS += -DBIPR=ON

# Assumes "make" is GNU make, turns into fork bomb if it finds Solaris make
COMPONENT_BUILD_ENV += PATH="/usr/gnu/bin:$(PATH)"

COMPONENT_POST_INSTALL_ACTION=	\
	$(PYTHON) -m py_compile $(PROTO_DIR)/$(PYTHON_LIB)/libproxy.py

REQUIRED_PACKAGES += developer/build/autoconf
REQUIRED_PACKAGES += developer/build/automake
REQUIRED_PACKAGES += developer/build/cmake
REQUIRED_PACKAGES += developer/build/gnu-make
REQUIRED_PACKAGES += developer/build/pkg-config
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
