#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 erwinlem
#

BUILD_STYLE=cmake
OPENSSL_VERSION= 3.1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		domoticz
COMPONENT_VERSION=	2024.4
COMPONENT_SUMMARY=	Open source Home Automation System
COMPONENT_PROJECT_URL=	http://www.domoticz.com/
COMPONENT_FMRI=		network/${COMPONENT_NAME}
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/domoticz/domoticz/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:d87113d7cacd0b52b9126fcc1ef24e140a4f7042d5bc6262e86e4b4752f5cf38
COMPONENT_LICENSE=	GPL-3.0 license
COMPONENT_LICENSE_FILE=	License.txt

TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk

CMAKE_PREFIX = /usr/${COMPONENT_NAME}

COMPONENT_PRE_CMAKE_ACTION  = (git clone https://github.com/domoticz/minizip.git $(SOURCE_DIR)/extern/minizip)

CXXFLAGS += -pthreads
LDFLAGS += -lnsl -lsocket -lsqlite3

CMAKE_OPTIONS+= -DUSE_BUILTIN_JSONCPP=OFF
#CMAKE_OPTIONS+= -DUSE_BUILTIN_MINIZIP=OFF
CMAKE_OPTIONS+= -DUSE_BUILTIN_MQTT=OFF
CMAKE_OPTIONS+= -DUSE_BUILTIN_SQLITE=OFF

# Build dependencies
REQUIRED_PACKAGES+= library/cereal

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/jsoncpp
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += network/mosquitto
REQUIRED_PACKAGES += runtime/lua-54
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/usb/libusb
REQUIRED_PACKAGES += web/curl
