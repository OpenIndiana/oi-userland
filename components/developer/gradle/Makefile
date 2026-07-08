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
# Copyright 2026 Geoff Weiss
#

BUILD_STYLE=archive
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gradle
COMPONENT_VERSION=	9.6.1
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)-bin.zip
COMPONENT_FMRI=		developer/gradle
COMPONENT_CLASSIFICATION=	Development/Java
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://gradle.org/
COMPONENT_ARCHIVE_HASH=	\
	sha256:9c0f7faeeb306cb14e4279a3e084ca6b596894089a0638e68a07c945a32c9e14
COMPONENT_ARCHIVE_URL=\
	https://services.gradle.org/distributions/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		Apache-2.0, MPL 2.0, epl-2.0, BSD, Eclipse 1.0, LGPL 2.1, CDDL-1.0, MIT, 3-Clause BSD, EPL-1.0
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_SUMMARY=	Adaptable, fast automation for all

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Needed for GNU ln
PATH=$(PATH.gnu)

build: 

install: prep
	mkdir -p $(PROTO_DIR)/usr/share/gradle
	mkdir -p $(PROTO_DIR)/usr/bin
	cp -pr $(SOURCE_DIR)/* $(PROTO_DIR)/usr/share/gradle
	ln -frs $(PROTO_DIR)/usr/share/gradle/bin/* $(PROTO_DIR)/usr/bin
	find $(PROTO_DIR) -name \*.bat -delete

clean::
	rm -rf $(BUILD_DIR)
	rm -rf $(SOURCE_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
