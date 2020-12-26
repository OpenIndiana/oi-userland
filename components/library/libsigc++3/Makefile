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
# Copyright 2021 Andreas Wacknitz
#

BUILD_BITS= 32_and_64
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	libsigc++
COMPONEN_MAJOR_VERSION=	3.0
COMPONENT_VERSION= $(COMPONEN_MAJOR_VERSION).6
COMPONENT_FMRI= library/c++/sigcpp3
COMPONENT_SUMMARY= Libsigc++ - a library that implements a typesafe callback system for standard C++
COMPONENT_CLASSIFICATION=	Development/C++ 
COMPONENT_PROJECT_URL = https://libsigc.sourceforge.net
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:b70edcf4611651c54a426e109b17196e1fa17da090592a5000e2d134c03ac5ce
COMPONENT_ARCHIVE_URL=	https://ftp.gnome.org/pub/GNOME/sources/libsigc++/$(COMPONEN_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= LGPLv3 

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += -Dbuild-documentation=true

# Prevent test failure:
unexport SHELLOPTS

COMPONENT_TEST_ENV += LD_LIBRARY_PATH="$(PROTOUSRLIBDIR):$(PROTOUSRLIBDIR64):"

# The tests need $(PROTOUSRLIBDIR) and $(PROTOUSRLIBDIR64) and pre-publish provides them:
test: pre-publish

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
