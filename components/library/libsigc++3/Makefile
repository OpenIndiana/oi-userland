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
# Copyright 2023 Friedrich Kink
#

BUILD_BITS= 64
BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libsigc++
COMPONEN_MAJOR_VERSION=	3.6
COMPONENT_VERSION=      $(COMPONEN_MAJOR_VERSION).0
COMPONENT_SUMMARY=      Libsigc++ - a library that implements a typesafe callback system for standard C++
COMPONENT_PROJECT_URL=  https://libsigc.sourceforge.net
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:c3d23b37dfd6e39f2e09f091b77b1541fbfa17c4f0b6bf5c89baef7229080e17
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/libsigc++/$(COMPONEN_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/c++/sigcpp3
COMPONENT_CLASSIFICATION=Development/C++ 
COMPONENT_LICENSE=      LGPLv3 
COMPONENT_LICENSE_FILE= COPYING 

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += -Dbuild-documentation=true

# Prevent test failure:
unexport SHELLOPTS

COMPONENT_TEST_ENV += LD_LIBRARY_PATH="$(PROTOUSRLIBDIR):$(PROTOUSRLIBDIR64):"

COMPONENT_TEST_TRANSFORMS += '-e "s/[0-9]*\.[0-9]*s//" '
COMPONENT_TEST_TRANSFORMS += '-e "/^Full log written.*/d" '

# The tests need $(PROTOUSRLIBDIR) and $(PROTOUSRLIBDIR64) and pre-publish provides them:
test: pre-publish

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
