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
OPENSSL_VERSION= 3.1
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mosquitto
COMPONENT_VERSION=	2.0.17
COMPONENT_SUMMARY=	Eclipse Mosquitto - An open source MQTT broker
COMPONENT_PROJECT_URL=	https://mosquitto.org/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://mosquitto.org/files/source/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:3be7a911236567c1a9fbe25baf3e3167004ba4a0c151a448ef1f7fc077dba52f
COMPONENT_FMRI=		network/${COMPONENT_NAME}
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_LICENSE=	Eclipse Public License 2.0
COMPONENT_LICENSE_FILE=	epl-v20

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

LDFLAGS += -lsocket

CMAKE_OPTIONS += -DCMAKE_INSTALL_SYSCONFDIR=/etc

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/security/openssl-31
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
