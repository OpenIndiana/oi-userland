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

BUILD_STYLE= cmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mosquitto
COMPONENT_VERSION=	2.0.20
COMPONENT_SUMMARY=	Eclipse Mosquitto - An open source MQTT broker
COMPONENT_PROJECT_URL=	https://mosquitto.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://mosquitto.org/files/source/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:ebd07d89d2a446a7f74100ad51272e4a8bf300b61634a7812e19f068f2759de8
COMPONENT_FMRI=		network/${COMPONENT_NAME}
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_LICENSE=	Eclipse Public License 2.0
COMPONENT_LICENSE_FILE=	epl-v20

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(XPG7MODE)

LDFLAGS += -lsocket

CMAKE_OPTIONS += -DCMAKE_INSTALL_SYSCONFDIR=/etc

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
