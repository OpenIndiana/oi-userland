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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	jruby
COMPONENT_VERSION= 	9.1.7.0
COMPONENT_SUMMARY= 	Java implementation of the Ruby programming language
COMPONENT_FMRI = 	runtime/java/jruby
COMPONENT_CLASSIFICATION = Development/Ruby
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_NAME)-src-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:748141906ec01c477211a5c0af090d9e8f2d6b20523c26cb87761e0b8be09f59
COMPONENT_ARCHIVE_URL= \
  https://s3.amazonaws.com/jruby.org/downloads/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://jruby.org
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_LICENSE = EPLv1.0, GPLv2, LGPLv2.1

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV += JAVA_HOME="$(JAVA_HOME)"

COMPONENT_BUILD_ACTION =  cd $(@D); $(ENV) $(COMPONENT_BUILD_ENV) mvn install

COMPONENT_INSTALL_ACTION =  cd $(@D) ;\
	rm -fr $(PROTO_DIR);\
	mkdir -p $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION);\
	cp -r $(BUILD_DIR_32)/bin $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION) ;\
	cp -r $(BUILD_DIR_32)/docs $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION);\
	cp -r $(BUILD_DIR_32)/lib $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION) ;\
	cp -r $(BUILD_DIR_32)/samples $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION) ;\
	$(GSED) -i '' -e 's:usr/local/bin/ruby:usr/bin/ruby:g' \
		$(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION)/lib/target/rubygems/gems/racc-1.4.14-java/bin/{racc2y,y2racc}



build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += runtime/ruby-22
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
