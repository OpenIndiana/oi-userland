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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2018 Olaf Bohlen.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	maven
COMPONENT_VERSION= 3.6.1
COMPONENT_FMRI= developer/build/maven
COMPONENT_CLASSIFICATION = Development/Java
COMPONENT_SUMMARY= Apache Maven is a software project management and comprehension tool
COMPONENT_PROJECT_URL = http://maven.apache.org
COMPONENT_SRC= apache-maven-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC)-bin.tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:2528c35a99c30f8940cc599ba15d34359d58bec57af58c1075519b8cd33b69e7
COMPONENT_ARCHIVE_URL= \
  http://archive.apache.org/dist/maven/maven-3/$(COMPONENT_VERSION)/binaries/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= Apache 2.0
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

build:

install: prep
	[ -d $(PROTO_DIR)/usr/share/maven ] || mkdir -p $(PROTO_DIR)/usr/share/maven
	cp -r $(SOURCE_DIR)/* $(PROTO_DIR)/usr/share/maven/

clean::
	rm -rf $(BUILD_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
