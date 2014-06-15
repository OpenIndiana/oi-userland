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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= postgresql-jdbc

COMPONENT_VERSION= 9.2-1003
IPS_COMPONENT_VERSION= 9.2.1003
COMPONENT_SUMMARY=JDBC driver for PostgreSQL
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION).src
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:d61449b8a17ce540b26437382c33a59a49a94c578c943fccf91139ee06478968
COMPONENT_ARCHIVE_URL= \
  http://jdbc.postgresql.org/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://jdbc.postgresql.org/

include ../../make-rules/prep.mk
include ../../make-rules/ant.mk
include ../../make-rules/ips.mk

JAVA_HOME=	$(JAVA6_HOME)
COMPONENT_BUILD_ARGS =

build: $(BUILD_32)

install: $(BUILD_32)
	$(MKDIR) -p $(PROTO_DIR)/usr/postgres/jdbc && \
	$(CP) $(BUILD_DIR_32)/jars/postgresql.jar $(PROTO_DIR)/usr/postgres/jdbc/postgresql-jdbc4.jar
