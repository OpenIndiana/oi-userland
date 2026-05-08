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

BUILD_STYLE=archive
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		groovy
COMPONENT_MAJOR_VERSION=	5.0
COMPONENT_MINOR_VERSION=	6
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_ARCHIVE=	apache-$(COMPONENT_NAME)-binary-$(COMPONENT_VERSION).zip
COMPONENT_FMRI=		developer/groovy-50
COMPONENT_CLASSIFICATION=	Development/Java
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://groovy-lang.org/
COMPONENT_ARCHIVE_HASH=	\
	sha256:14300bca33dc6a911ed5e2c6bc5b83b63fa8a5278e791820ff7e70fc76d06e1d
COMPONENT_ARCHIVE_URL=\
	https://groovy.jfrog.io/artifactory/dist-release-local/groovy-zips/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		Apache-2.0, BSD, MIT, Eclipse 1.0, Eclipse 2.0, Public Domain, 3-clause BSD, JSR223
COMPONENT_LICENSE_FILE= groovy.license
COMPONENT_SUMMARY=	Groovy is a Java-based scripting language

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

build:

install: prep
	mkdir -p $(PROTO_DIR)/usr/share/groovy-$(COMPONENT_MAJOR_VERSION)
	mkdir -p $(PROTO_DIR)/usr/bin
	cp -rf $(SOURCE_DIR)/bin $(PROTO_DIR)/usr/share/groovy-$(COMPONENT_MAJOR_VERSION)
	cp -rf $(SOURCE_DIR)/conf $(PROTO_DIR)/usr/share/groovy-$(COMPONENT_MAJOR_VERSION)
	cp -rf $(SOURCE_DIR)/grooid $(PROTO_DIR)/usr/share/groovy-$(COMPONENT_MAJOR_VERSION)
	cp -rf $(SOURCE_DIR)/lib $(PROTO_DIR)/usr/share/groovy-$(COMPONENT_MAJOR_VERSION)
	ln -frs $(PROTO_DIR)/usr/share/groovy-$(COMPONENT_MAJOR_VERSION)/bin/* $(PROTO_DIR)/usr/bin
	find $(PROTO_DIR) -name \*.bat -delete

clean::
	rm -rf $(BUILD_DIR)
	rm -rf $(SOURCE_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
