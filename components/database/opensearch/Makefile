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
# Copyright 2022 Niklas Poslovski
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= opensearch
COMPONENT_VERSION= 2.7.0
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= Open source distributed and RESTful search engine
COMPONENT_PROJECT_URL= https://opensearch.org
COMPONENT_SRC=          OpenSearch-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://github.com/opensearch-project/OpenSearch/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:b002039009dce94fc25a1cbeade4f35a725b517f717b6bbab95b42dfbb59f20b
COMPONENT_FMRI= database/opensearch
COMPONENT_CLASSIFICATION= System/Databases
COMPONENT_LICENSE= APACHE 2.0
COMPONENT_LICENSE_FILE= LICENSE.txt

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Build fails with Java 21
JAVA_VERSION = 17

COMPONENT_BUILD_ACTION = cd $(@D); $(ENV) PATH="$(PATH)" GRADLE_USER_HOME=$(@D)/.gradle ./gradlew localDistro

COMPONENT_INSTALL_ACTION = $(ENV) DIR=$(@D) COMPONENT_VERSION=$(COMPONENT_VERSION) PROTO_DIR=$(PROTO_DIR) files/install.sh

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
