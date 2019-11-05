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
# Copyright 2016-2018 Jim Klimov
#
include ../../../make-rules/shared-macros.mk

# NOTE: Initial jenkins recipe had one component for both the JAR
# file downloads and the OpenIndiana integration helper packages.
# Due to this, initial version for helper packages starts from that.

COMPONENT_NAME=		jenkins
COMPONENT_VERSION=	2.65
COMPONENT_REVISION=	3
COMPONENT_FMRI=		developer/jenkins
COMPONENT_CLASSIFICATION=	Web Services/Application and Web Servers
COMPONENT_PROJECT_URL=	http://jenkins-ci.org/
COMPONENT_LICENSE=		MIT
COMPONENT_LICENSE_FILE= jenkins.license
COMPONENT_SUMMARY=	Jenkins is a Java-based CI automation server

include $(WS_MAKE_RULES)/ips.mk

download:

prep:

clean::
	$(RM) -r $(BUILD_DIR)

clobber:: clean

build:
	$(MKDIR) $(BUILD_DIR)

install:
	$(MKDIR) $(PROTO_DIR)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += runtime/java/openjdk8
