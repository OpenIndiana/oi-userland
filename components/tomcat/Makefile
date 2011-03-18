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
COMPONENT_VERSION=	6.0.28
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:0df5e58518607ff738bbf440d829747df6acb9ce
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/tomcat/tomcat-6/v6.0.28/src/$(COMPONENT_ARCHIVE)

# Tomcat subcomponents
COMPONENT_ARCHIVE_1= commons-dbcp-1.4-src.tar.gz
COMPONENT_ARCHIVE_HASH_1= sha1:48702486eaba6ec40fb65e912c8f597d80654f54
COMPONENT_ARCHIVE_URL_1= http://archive.apache.org/dist/commons/dbcp/source/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_2= commons-pool-1.5.4-src.tar.gz
COMPONENT_ARCHIVE_HASH_2= sha1:18279249c27fee5bdedeaff169b9d1b70d135839
COMPONENT_ARCHIVE_URL_2= http://archive.apache.org/dist/commons/pool/source/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_3= eclipse-JDT-3.3.1.zip
COMPONENT_ARCHIVE_HASH_3= sha1:9628f715ef2e53dd295164eafd70a95f64292d27
COMPONENT_ARCHIVE_URL_3= http://archive.eclipse.org/eclipse/downloads/drops/R-3.3.1-200709211145/$(COMPONENT_ARCHIVE_3)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

TC_ENV=JAVA_HOME=$(JAVA_HOME)

# We have no proto area with Tomcat. Instead several transformation rules
# are used over mainly Tomcat output directory.
PKG_PROTO_DIRS =  $(COMPONENT_DIR)
PKG_PROTO_DIRS += $(BUILD_DIR_32)/output/build
PKG_PROTO_DIRS += $(BUILD_DIR_32)/output/build/webapps
PKG_PROTO_DIRS += $(COMPONENT_DIR)/Solaris
PUBLISH_TRANSFORMS += solaris-transform

GMAKE=ant
COMPONENT_BUILD_TARGETS=-Dbase.path=$(BUILD_DIR_32) download deploy
COMPONENT_BUILD_ENV+=$(TC_ENV)

# Create configuration backup archive for custom user's deployments.
# Move default web application to different location so we can package
# it in separate package and instead provide basic one.
COMPONENT_POST_BUILD_ACTION= \
	(cd $(@D)/output/build ; \
	    gtar cfz conf/CONF.tar.gz conf/* ; \
	    $(MV) webapps/ROOT webapps/ROOT.example )

build:	$(BUILD_32)

install: build

test:  build
	@cd $(BUILD_DIR_32)/test; $(ENV) $(TC_ENV) ant -Djunit.home=/usr/share/lib/java

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
