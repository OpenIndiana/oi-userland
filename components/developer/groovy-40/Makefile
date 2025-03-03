#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016-2017 Jim Klimov
#

BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		groovy
COMPONENT_MAJOR_VERSION=	4.0
COMPONENT_MINOR_VERSION=	26
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_ARCHIVE=	apache-$(COMPONENT_NAME)-binary-$(COMPONENT_VERSION).zip
COMPONENT_FMRI=		developer/groovy-40
COMPONENT_CLASSIFICATION=	Development/Java
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://groovy-lang.org/
COMPONENT_ARCHIVE_HASH=	\
	sha256:3be6880c6de70eada2f3f5c69e1e94953e0b0c4e33c4604c1040d05dddeaed92
COMPONENT_ARCHIVE_URL=\
	https://groovy.jfrog.io/artifactory/dist-release-local/groovy-zips/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		Apache-2.0, BSD, MIT, Eclipse 1.0, Eclipse 2.0, Public Domain, 3-clause BSD, JSR223
COMPONENT_LICENSE_FILE= groovy.license
COMPONENT_SUMMARY=	Groovy is a Java-based scripting language

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION += ($(CP) $(COMPONENT_DIR)/files/Makefile $(SOURCE_DIR))

COMPONENT_COPY_ACTION = $(CP) -r $(SOURCE_DIR)/* $(@D)/

COMPONENT_INSTALL_ENV += GROOVY_MAJOR_VERSION=$(COMPONENT_MAJOR_VERSION)

COMPONENT_POST_INSTALL_ACTION = $(FIND) $(PROTO_DIR) -name \*.bat -delete

# JDK does not get picked up by gmake REQUIRED_PACKAGES
REQUIRED_PACKAGES += runtime/java/openjdk21

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
