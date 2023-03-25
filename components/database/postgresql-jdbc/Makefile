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
# Copyright 2017 Alexander Pyhalov.  All rights reserved.
# Copyright 2022 Niklas Poslovski
#
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	postgresql-jdbc
COMPONENT_VERSION=	42.6.0
COMPONENT_SUMMARY=	JDBC driver for PostgreSQL
COMPONENT_SRC=	postgresql-$(COMPONENT_VERSION)-jdbc-src
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).src.tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f6849b3963255a724017b475309de3884b301fb3cbdcdb3ff411c2df384a5dc4
COMPONENT_ARCHIVE_URL=	https://jdbc.postgresql.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://jdbc.postgresql.org/
COMPONENT_FMRI=	database/postgres/connector/jdbc
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV += JAVA_HOME=$(JAVA_HOME)

COMPONENT_BUILD_ACTION = cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) \
						 mvn install

COMPONENT_INSTALL_ACTION = $(MKDIR) -p $(PROTO_DIR)/usr/postgres/jdbc && \
        $(CP) $(BUILD_DIR_64)/target/postgresql-*.jar $(PROTO_DIR)/usr/postgres/jdbc/postgresql-jdbc4.jar


REQUIRED_PACKAGES += developer/build/maven
REQUIRED_PACKAGES += developer/java/openjdk8

# Auto-generated dependencies
