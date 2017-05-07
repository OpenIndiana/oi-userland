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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	postgresql-jdbc
COMPONENT_VERSION=	42.0.0
COMPONENT_SUMMARY=	JDBC driver for PostgreSQL
COMPONENT_SRC=	$(COMPONENT_NAME)-42.0-0.src
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).src.tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:99eaa62b49c9ef2be6ad6509fbb3ca8d00e7da6da414cfef574763555b77e1e4
COMPONENT_ARCHIVE_URL= \
  http://jdbc.postgresql.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://jdbc.postgresql.org/
COMPONENT_FMRI=	database/postgres/connector/jdbc
COMPONENT_CLASSIFICATION=	System/Databases
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV += JAVA_HOME=$(JAVA_HOME)

COMPONENT_BUILD_ACTION = cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) \
				mvn install

COMPONENT_INSTALL_ACTION = $(MKDIR) -p $(PROTO_DIR)/usr/postgres/jdbc && \
        $(CP) $(BUILD_DIR_32)/pgjdbc/target/postgresql-*.jar $(PROTO_DIR)/usr/postgres/jdbc/postgresql-jdbc4.jar


build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += developer/build/maven
REQUIRED_PACKAGES += developer/java/openjdk8
