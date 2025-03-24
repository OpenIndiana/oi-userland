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

COMPONENT_NAME=			apache-tomcat
COMPONENT_VERSION=		11.0.5
COMPONENT_SUMMARY=		Tomcat 11 Servlet/JSP Container
COMPONENT_PROJECT_URL=	https://tomcat.apache.org/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)-src
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:e7d24007377dd039b7f72fba90f639ea3fe4218c6d48c51b63832c1935cb453b
COMPONENT_ARCHIVE_URL=	https://archive.apache.org/dist/tomcat/tomcat-11/v$(COMPONENT_VERSION)/src/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			web/java-servlet/tomcat-11
COMPONENT_CLASSIFICATION=	Web Services/Application and Web Servers
COMPONENT_LICENSE=		Apache-2.0 AND EPL-2.0 AND CDDL-1.0
COMPONENT_LICENSE_FILE=		LICENSE

COMPONENT_SUMMARY.tomcat-admin =	$(COMPONENT_SUMMARY) - admin applications
COMPONENT_FMRI.tomcat-admin =		$(COMPONENT_FMRI)/tomcat-admin

COMPONENT_SUMMARY.tomcat-examples =	$(COMPONENT_SUMMARY) - example applications
COMPONENT_FMRI.tomcat-examples =	$(COMPONENT_FMRI)/tomcat-examples

# By default the install is same as build and so we need to override it
INSTALL_TARGET = $(INSTALL_$(MK_BITS))

# Enable tests
TEST_TARGET = $(TEST_$(MK_BITS))

include $(WS_MAKE_RULES)/common.mk

# Install
COMPONENT_PRE_INSTALL_ACTION += $(MKDIR) $(PROTOUSRDIR) ;
COMPONENT_INSTALL_CMD = $(CP) -pr
COMPONENT_INSTALL_ARGS = output/build
COMPONENT_INSTALL_TARGETS = $(PROTOUSRDIR)/tomcat11

# Change the tomcat install directory layout
COMPONENT_POST_INSTALL_ACTION += $(MKDIR) $(PROTOVARDIR)/tomcat11 ;
COMPONENT_POST_INSTALL_ACTION += $(MV) $(PROTOUSRDIR)/tomcat11/conf $(PROTOVARDIR)/tomcat11 ;
COMPONENT_POST_INSTALL_ACTION += $(MV) $(PROTOUSRDIR)/tomcat11/webapps/docs $(PROTOUSRDIR)/tomcat11 ;
COMPONENT_POST_INSTALL_ACTION += $(MV) $(PROTOUSRDIR)/tomcat11/webapps $(PROTOVARDIR)/tomcat11 ;
COMPONENT_POST_INSTALL_ACTION += $(SYMLINK) ../../../usr/tomcat11/docs $(PROTOVARDIR)/tomcat11/webapps/docs ;
COMPONENT_POST_INSTALL_ACTION += $(MV) $(PROTOVARDIR)/tomcat11/webapps/ROOT $(PROTOVARDIR)/tomcat11/webapps/ROOT.example ;
# Create configuration backup archive for custom user's deployments.
COMPONENT_POST_INSTALL_ACTION += ( \
	cd $(PROTOVARDIR)/tomcat11 ; \
	$(RM) conf/CONF.tar.gz ; \
	$(GTAR) cfz conf/CONF.tar.gz conf/* ) ;

# Install additional files
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -D $(COMPONENT_DIR)/files/http-tomcat.xml $(PROTOLIBDIR)/svc/manifest/network/http-tomcat11.xml ;
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -D $(COMPONENT_DIR)/files/http-tomcat $(PROTOLIBDIR)/svc/method/http-tomcat11 ; \
	$(GSED) -i -e 's|%JAVA_HOME%|$(JAVA_HOME)|' $(PROTOLIBDIR)/svc/method/http-tomcat11 ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -D $(COMPONENT_DIR)/files/index.htm $(PROTOVARDIR)/tomcat11/webapps/ROOT/index.htm ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -D $(COMPONENT_DIR)/files/index.jsp $(PROTOVARDIR)/tomcat11/webapps/ROOT/index.jsp ;
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -D $(COMPONENT_DIR)/files/tomcat.1m $(PROTOUSRSHAREMAN1MDIR)/tomcat11.1m ; \
	$(SYMLINK) tomcat11.1m $(PROTOUSRSHAREMAN1MDIR)/tomcat.1m ;

# Override the default test target
COMPONENT_TEST_TARGETS = test

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/java/openjdk21
REQUIRED_PACKAGES += shell/ksh93
