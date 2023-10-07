#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE = cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         qtkeychain-qt5
COMPONENT_VERSION=      0.14.1
COMPONENT_PROJECT_URL=  https://github.com/frankosterfeld/qtkeychain
COMPONENT_SUMMARY=      Provides support for secure credentials storage
COMPONENT_FMRI=         library/qt5/qtkeychain
COMPONENT_SRC=          qtkeychain-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:afb2d120722141aca85f8144c4ef017bd74977ed45b80e5d9e9614015dadd60c
COMPONENT_ARCHIVE_URL=  https://github.com/frankosterfeld/qtkeychain/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION=       Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CMAKE_OPTIONS += -DQt5_DIR=$(QT5_LIBDIR)/cmake/Qt5

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += system/library
