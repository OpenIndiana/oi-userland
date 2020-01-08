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
# Copyright 2017 Alexander Pyhalov
#
BUILD_BITS=64
BUILD_STYLE=justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	jruby
COMPONENT_VERSION= 	9.1.17.0
COMPONENT_SUMMARY= 	Java implementation of the Ruby programming language
COMPONENT_FMRI = 	runtime/java/jruby
COMPONENT_CLASSIFICATION = Development/Ruby
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_NAME)-src-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:b66d7c14f85075afdabb5ebf5950804c5a5d5c1d05ab833f580f04ee709b5773
COMPONENT_ARCHIVE_URL= \
  https://s3.amazonaws.com/jruby.org/downloads/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://jruby.org
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_LICENSE = EPLv1.0, GPLv2, LGPLv2.1

TEST_TARGET=$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ENV += JAVA_HOME="$(JAVA_HOME)"

COMPONENT_BUILD_ACTION =  cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) mvn install

COMPONENT_INSTALL_ACTION =  cd $(@D) ;\
	rm -fr $(PROTO_DIR);\
	mkdir -p $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION);\
	cp -r $(BUILD_DIR_64)/bin $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION) ;\
	cp -r $(BUILD_DIR_64)/docs $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION);\
	cp -r $(BUILD_DIR_64)/lib $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION) ;\
	cp -r $(BUILD_DIR_64)/samples $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION) ;\
	gfind $(PROTO_DIR) -regextype posix-extended -regex '.*\.(bat|dll|exe)' -print -delete; \
	rm -r $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION)/lib/jni/{Darwin,*-Linux,*-Windows,*-AIX,*-*BSD}

# Build dependencies
REQUIRED_PACKAGES += runtime/ruby-23

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/java/openjdk8
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
