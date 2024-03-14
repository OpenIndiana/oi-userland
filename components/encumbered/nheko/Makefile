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

COMPONENT_NAME=         nheko
COMPONENT_VERSION=      0.11.3
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      Desktop client for Matrix using Qt and C++20.
COMPONENT_PROJECT_URL=  https://nheko-reborn.github.io/
COMPONENT_FMRI=         communication/im/nheko
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:f285156884a3a0c6870f3fba89c13d1fd70c8727bd179d8310b13819f8a63a37
COMPONENT_ARCHIVE_URL=	https://github.com/Nheko-Reborn/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_CLASSIFICATION=       Applications/Internet
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -Wl,-rpath,$(QT5_LIBDIR)
CMAKE_OPTIONS += -DCMAKE_PREFIX_PATH=$(QT5_LIBDIR)/cmake

# Manually added build dependencies
REQUIRED_PACKAGES += library/c++/nlohmann-json
REQUIRED_PACKAGES += database/lmdb/library/c++/lmdbxx

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/lmdb
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/bad
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/c++/spdlog
REQUIRED_PACKAGES += library/cmark
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/olm
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/qt5/qtkeychain
REQUIRED_PACKAGES += network/chat/mtxclient
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/xcb-util-wm
