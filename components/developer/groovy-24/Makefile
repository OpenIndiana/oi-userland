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
# Copyright 2016 Jim Klimov
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		groovy
COMPONENT_MAJOR_VERSION=	2.4
COMPONENT_MINOR_VERSION=	8
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_REVISION=	1
COMPONENT_ARCHIVE=	apache-$(COMPONENT_NAME)-binary-$(COMPONENT_VERSION).zip
COMPONENT_FMRI=		developer/groovy-24
COMPONENT_CLASSIFICATION=	Development/Java
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://groovy-lang.org/
COMPONENT_ARCHIVE_HASH=	\
	sha256:668a65ea17037371a1952cca5f42ebc03329e15d3619aacb4c7dd5f4b39a8dfd
COMPONENT_ARCHIVE_URL=	https://bintray.com/artifact/download/groovy/maven/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		Apache-2.0,BSD,MIT,Eclipse,PublicDomain
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_SUMMARY=	Groovy is a Java-based scripting language

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION += (cp $(COMPONENT_DIR)/files/Makefile $(SOURCE_DIR))

COMPONENT_COPY_ACTION = cp -r $(SOURCE_DIR)/* $(@D)/

COMPONENT_INSTALL_ENV += GROOVY_MAJOR_VERSION=$(COMPONENT_MAJOR_VERSION)

COMPONENT_POST_INSTALL_ACTION = $(FIND) $(PROTO_DIR) -name \*.bat -delete

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/java/openjdk7
REQUIRED_PACKAGES += developer/java/openjdk8
REQUIRED_PACKAGES += runtime/java/openjdk7
REQUIRED_PACKAGES += runtime/java/openjdk8
REQUIRED_PACKAGES += system/library
