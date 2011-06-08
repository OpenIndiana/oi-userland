#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		apache-tomcat
COMPONENT_VERSION=	6.0.32
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:ec94c511e54da2b02dd2ba45b9fd1703d5771a45
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/tomcat/tomcat-6/v$(COMPONENT_VERSION)/src/$(COMPONENT_ARCHIVE)

# Tomcat subcomponents
COMPONENT_ARCHIVE_1= commons-dbcp-1.4-src.tar.gz
COMPONENT_ARCHIVE_HASH_1= sha1:48702486eaba6ec40fb65e912c8f597d80654f54
COMPONENT_ARCHIVE_URL_1= http://archive.apache.org/dist/commons/dbcp/source/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_2= commons-pool-1.5.5-src.tar.gz
COMPONENT_ARCHIVE_HASH_2= sha1:375408d445be1b87e935bb8e68cc9f746a3b59fb
COMPONENT_ARCHIVE_URL_2= http://archive.apache.org/dist/commons/pool/source/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_3= ecj.jar
COMPONENT_ARCHIVE_HASH_3= sha1:f4ddfbb80cb97b0bdfa8730102db9fec1630a983
COMPONENT_ARCHIVE_URL_3= http://archive.eclipse.org/eclipse/downloads/drops/R-3.3.1-200709211145/$(COMPONENT_ARCHIVE_3)

include ../../make-rules/prep.mk
include ../../make-rules/ant.mk
include ../../make-rules/ips.mk

COMPONENT_BUILD_ARGS=-Dbase.path=$(BUILD_DIR_32) -Dtomcat.build=$(PROTO_DIR)
COMPONENT_BUILD_TARGETS=download deploy

# Create configuration backup archive for custom user's deployments.
COMPONENT_POST_BUILD_ACTION= \
	(cd $(PROTO_DIR) ; $(RM) conf/CONF.tar.gz ; \
	    gtar cfz conf/CONF.tar.gz conf/* )

build:	$(BUILD_32)

install: build

test:  build
	@cd $(BUILD_DIR_32)/test; $(ENV) $(COMPONENT_BUILD_ENV) \
	    $(ANT) $(COMPONENT_BUILD_ARGS) -Djunit.home=/usr/share/lib/java

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
