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

BUILD_STYLE=ant
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tomcat
COMPONENT_VERSION=	11.0.2
COMPONENT_PROJECT_URL=	https://tomcat.apache.org/
COMPONENT_SRC_NAME=	apache-tomcat
COMPONENT_SRC=		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:94885a2591a1427dabae36cf2dc8d1839d25b05a3aee32aab9721431f6c1032c
COMPONENT_ARCHIVE_URL=	https://archive.apache.org/dist/tomcat/tomcat-11/v$(COMPONENT_VERSION)/src/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

# Needed when compiling jdbc-pool module
CLASSPATH=$(PROTO_DIR)/lib:$(PROTO_DIR)/bin

# Tomcat tests doesn't like cloning.
CLONEY_ARGS += CLONEY_MODE=copy
COMPONENT_PRE_BUILD_ACTION= \
	$(CP) -r $(SOURCE_DIR)/* $(@D);

# Set up tomcat into install directory structure that Oracle defined for Solaris
# Also, create configuration backup archive for custom user's deployments.
COMPONENT_POST_BUILD_ACTION= \
	($(MKDIR) -p $(PROTO_DIR)/usr/tomcat11; \
         $(MKDIR) -p $(PROTO_DIR)/var/tomcat11; \
         $(CP) -pr $(@D)/output/build/bin $(PROTO_DIR)/usr/tomcat11; \
         $(CP) -pr $(@D)/output/build/lib $(PROTO_DIR)/usr/tomcat11; \
         $(CP) -pr $(@D)/output/build/conf $(PROTO_DIR)/var/tomcat11; \
         $(CP) -pr $(@D)/output/build/webapps $(PROTO_DIR)/var/tomcat11; \
         $(CP) -pr $(@D)/output/build/webapps/docs $(PROTO_DIR)/usr/tomcat11; \
         $(RM) -rf $(PROTO_DIR)/var/tomcat11/webapps/docs; \
         $(MV) $(PROTO_DIR)/var/tomcat11/webapps/ROOT $(PROTO_DIR)/var/tomcat11/webapps/ROOT.example; \
         cd $(PROTO_DIR)/var/tomcat11 ; $(RM) conf/CONF.tar.gz ; \
	 gtar cfz conf/CONF.tar.gz conf/* )

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Build dependencies
REQUIRED_PACKAGES += developer/build/ant

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/java/openjdk21
REQUIRED_PACKAGES += shell/ksh93
