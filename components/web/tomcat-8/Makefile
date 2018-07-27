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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tomcat
COMPONENT_VERSION=	8.0.53
COMPONENT_PROJECT_URL=	http://tomcat.apache.org/
COMPONENT_SRC_NAME=	apache-tomcat
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8e5f62134d65f99f7bafced8c06de1ac17c135dc2aeb909a8032954ce875c70b
COMPONENT_ARCHIVE_URL=	http://archive.apache.org/dist/tomcat/tomcat-8/v$(COMPONENT_VERSION)/src/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/tomcat

# Tomcat subcomponents
COMPONENT_ARCHIVE_1= ecjsrc-4.6.3.jar
COMPONENT_ARCHIVE_HASH_1= \
    sha256:f4be12aeaa50d54e883e75ee524c69ec9ed6a7c74bce4ef70d4adaff9a7e8e85
COMPONENT_ARCHIVE_URL_1= http://archive.eclipse.org/eclipse/downloads/drops4/R-4.6.3-201703010400/$(COMPONENT_ARCHIVE_1)

TPNO=			26981

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ant.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL=0

COMPONENT_BUILD_ARGS=-Dbase.path=$(BUILD_DIR_32) -Dtomcat.build=$(PROTO_DIR)

ifeq ($(strip $(USERLAND_ARCHIVES)),)
  ARCHIVES_LOCATION=$(COMPONENT_DIR)
else 
  ARCHIVES_LOCATION=$(USERLAND_ARCHIVES)
endif

# Tomcat tests doesn't like cloning.
CLONEY=echo
COMPONENT_PRE_BUILD_ACTION= \
	$(CP) -r $(SOURCE_DIR)/* $(@D);

# Build ECJ jar from sources.
COMPONENT_PRE_BUILD_ACTION+= \
	($(MKDIR) $(@D)/ECJ/scripts/binary/META-INF; cd $(@D)/ECJ ; \
	    $(JAVA_HOME)/bin/jar xf $(ARCHIVES_LOCATION)/$(COMPONENT_ARCHIVE_1); \
	    $(CP) META-INF/MANIFEST.MF scripts/binary/META-INF/; \
	    JAVA_HOME="$(JAVA_HOME)" LC_ALL="en_US.UTF-8" JAVA_TOOL_OPTIONS="-Dfile.encoding=UTF-8" $(ANT) )

# Create configuration backup archive for custom user's deployments.
COMPONENT_POST_BUILD_ACTION= \
	(cd $(PROTO_DIR) ; $(RM) conf/CONF.tar.gz ; \
	    gtar cfz conf/CONF.tar.gz conf/* )

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:	$(BUILD_32)

install: build

test:	$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += developer/build/ant
REQUIRED_PACKAGES += developer/java/openjdk8

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/java/openjdk8
