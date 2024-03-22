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
# Copyright (c) 2015, 2023, Oracle and/or its affiliates.
# Copyright 2023 Andreas Wacknitz
#

BUILD_BITS= 64_and_32
BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_COMMON_TEST_MASTER= false
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libproxy
COMPONENT_VERSION=      0.4.18
COMPONENT_REVISION=		2
COMPONENT_SUMMARY=      Libproxy is a library that provides automatic proxy configuration management
COMPONENT_PROJECT_URL=  https://libproxy.github.io/libproxy/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:69b5856e9ea42c38ac77e6b8c92ffc86a71d341fef74e77bef85f9cc6c47a4b1
COMPONENT_ARCHIVE_URL=	https://github.com/libproxy/libproxy/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			library/libproxy
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CFLAGS += $(XPG6MODE)
CXXFLAGS += -std=c++11

# Our Perl is 64-bit, so don't deliver Perl bindings for 32-bit build.
CMAKE_OPTIONS.32 = -DWITH_PERL=OFF
CMAKE_OPTIONS.64 = -DWITH_PERL=ON

# Our Python is 64-bit only, so don't deliver Python bindings for 32-bit build.
CMAKE_OPTIONS.32 = -DWITH_PYTHON3=OFF
CMAKE_OPTIONS.64 = -DWITH_PYTHON3=ON
CMAKE_OPTIONS.64 += -DPYTHON3_EXECUTABLE="$(PYTHON)"
CMAKE_OPTIONS.64 += -DPYTHON3_SITEPKG_DIR=$(PYTHON_LIB)

CMAKE_OPTIONS += -DINCLUDE_INSTALL_DIR="$(USRINCDIR)/$(COMPONENT_NAME)"
CMAKE_OPTIONS += -DPERL_VENDORINSTALL=ON
CMAKE_OPTIONS += -DPERL_EXECUTABLE=$(PERL)
CMAKE_OPTIONS += -DWITH_PYTHON2=OFF
CMAKE_OPTIONS += -DWITH_KDE=OFF
# Required for other components.
CMAKE_OPTIONS += -DWITH_GNOME3=ON
CMAKE_OPTIONS += -DWITH_VALA=ON
# Always build pacrunner as a module.
CMAKE_OPTIONS += -DBIPR=ON

LDFLAGS += -lsocket -lxnet -lnsl

# Assumes "make" is GNU make, turns into fork bomb if it finds illumos make
COMPONENT_BUILD_ENV += PATH=$(PATH)

COMPONENT_POST_INSTALL_ACTION=  \
    [ $(BITS) -eq 64 ] && $(PYTHON) -m py_compile $(PROTO_DIR)/$(PYTHON_LIB)/libproxy.py || true ;

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRBINDIR32) ;

# Move the 'proxy' binary to demos
$(INSTALL_64):	COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -d $(PROTOUSRDIR)/demo/jds/bin/ ;
$(INSTALL_64):	COMPONENT_POST_INSTALL_ACTION += $(MV) $(PROTOUSRBINDIR)/proxy $(PROTOUSRDIR)/demo/jds/bin/ ;

# Build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
