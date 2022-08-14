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

BUILD_BITS=64
BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= opensearch
COMPONENT_VERSION= 2.1.0
COMPONENT_SUMMARY= Open source distributed and RESTful search engine
COMPONENT_PROJECT_URL= https://opensearch.org
COMPONENT_FMRI= database/opensearch
COMPONENT_CLASSIFICATION= System/Databases
COMPONENT_SRC=          OpenSearch-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=  https://github.com/opensearch-project/OpenSearch/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:608f3de99bb98b570e19c565bde908e1fce074c3a6bd354da15c857348f00278
COMPONENT_LICENSE= APACHE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ACTION = cd $(@D); env JAVA_HOME="/usr/jdk/openjdk18.0.1" ./gradlew localDistro

COMPONENT_INSTALL_ACTION = env DIR=$(@D) COMPONENT_VERSION=$(COMPONENT_VERSION) PROTO_DIR=$(PROTO_DIR) files/install.sh

# Manually added dependencies
REQUIRED_PACKAGES += runtime/java/openjdk18
