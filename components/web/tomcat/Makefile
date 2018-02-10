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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tomcat
COMPONENT_VERSION=	6.0.48
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	http://tomcat.apache.org/
COMPONENT_SRC_NAME=	apache-tomcat
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:b39214d8e2214a82f611499e55b4a4a9fc844f0a881a129b6987310c782b0fa7
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/tomcat/tomcat-6/v$(COMPONENT_VERSION)/src/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/tomcat

# Tomcat subcomponents
COMPONENT_ARCHIVE_1= commons-dbcp-1.4-src.tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:f5f10846e79fc71121fe7402c61d71575506b01b59e719e974ebc4d99e6df283
COMPONENT_ARCHIVE_URL_1= http://archive.apache.org/dist/commons/dbcp/source/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_2= commons-pool-1.5.7-src.tar.gz
COMPONENT_ARCHIVE_HASH_2= \
    sha256:e9f414555c41e9584da1f6953af28208ece5cd4664ef2fea297e6a6aadc4377e
COMPONENT_ARCHIVE_URL_2= http://archive.apache.org/dist/commons/pool/source/$(COMPONENT_ARCHIVE_2)
COMPONENT_ARCHIVE_3= ecj-4.3.1.jar
COMPONENT_ARCHIVE_HASH_3= \
    sha256:5f86314f67dc57a0a9865265a48fd7831f16ab177c0c1349eea798c2c6297295
COMPONENT_ARCHIVE_URL_3= http://www.eclipse.org/downloads/download.php?file=/eclipse/downloads/drops4/R-4.3.1-201309111000/$(COMPONENT_ARCHIVE_3)
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ant.mk
include $(WS_MAKE_RULES)/ips.mk

ifeq ($(strip $(USERLAND_ARCHIVES)),)
  DISTFILES_LOCATION=\$${base.path}/../../
else 
  DISTFILES_LOCATION=$(USERLAND_ARCHIVES)
endif

COMPONENT_PREP_ACTION= ($(GSED) -i -e "s:__DISTFILES_LOCATION__:$(DISTFILES_LOCATION):" $(SOURCE_DIR)/build.properties.default)

COMPONENT_BUILD_ARGS=-Dbase.path=$(BUILD_DIR_32) -Dtomcat.build=$(PROTO_DIR)
COMPONENT_BUILD_TARGETS=download deploy

# Create configuration backup archive for custom user's deployments.
COMPONENT_POST_BUILD_ACTION= \
	(cd $(PROTO_DIR) ; $(RM) conf/CONF.tar.gz ; \
	    gtar cfz conf/CONF.tar.gz conf/* )

COMPONENT_TEST_DIR =		$(@D)/test
COMPONENT_TEST_ARGS =		$(COMPONENT_BUILD_ARGS) \
				-Djunit.home=/usr/share/lib/java
COMPONENT_TEST_TARGETS =

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:	$(BUILD_32)

install: build

test:  $(TEST_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/java/openjdk8
REQUIRED_PACKAGES += web/java-servlet/tomcat
