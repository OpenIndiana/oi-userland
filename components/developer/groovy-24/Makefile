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
BUILD_BITS=32
BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		groovy
COMPONENT_MAJOR_VERSION=	2.4
COMPONENT_MINOR_VERSION=	12
COMPONENT_REVISION=	1
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_ARCHIVE=	apache-$(COMPONENT_NAME)-binary-$(COMPONENT_VERSION).zip
COMPONENT_FMRI=		developer/groovy-24
COMPONENT_CLASSIFICATION=	Development/Java
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://groovy-lang.org/
COMPONENT_ARCHIVE_HASH=	\
	sha256:93b9a19c760c2af846afa0e9c78692d70186cdde36e070e9806fe11b84a8a7b6
COMPONENT_ARCHIVE_URL=\
	https://bintray.com/artifact/download/groovy/maven/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		Apache-2.0,BSD,MIT,Eclipse,PublicDomain
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_SUMMARY=	Groovy is a Java-based scripting language

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION += ($(CP) $(COMPONENT_DIR)/files/Makefile $(SOURCE_DIR))

COMPONENT_COPY_ACTION = $(CP) -r $(SOURCE_DIR)/* $(@D)/

COMPONENT_INSTALL_ENV += GROOVY_MAJOR_VERSION=$(COMPONENT_MAJOR_VERSION)

COMPONENT_POST_INSTALL_ACTION = $(FIND) $(PROTO_DIR) -name \*.bat -delete

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/java/openjdk7
REQUIRED_PACKAGES += developer/java/openjdk8
REQUIRED_PACKAGES += runtime/java/openjdk7
REQUIRED_PACKAGES += runtime/java/openjdk8
REQUIRED_PACKAGES += system/library
