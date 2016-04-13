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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= 	jruby
COMPONENT_VERSION= 	1.7.14
COMPONENT_SUMMARY= 	Java implementation of the Ruby programming language
COMPONENT_FMRI = 	runtime/java/jruby
COMPONENT_CLASSIFICATION = Development/Ruby
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_NAME)-src-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:24f08ce4cb8fd59b811885028e57efc79878e3dc0916e0f694c6d8e3518dc322
COMPONENT_ARCHIVE_URL= \
  https://s3.amazonaws.com/jruby.org/downloads/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://jruby.org

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk

COMPONENT_BUILD_ENV += JAVA_HOME="$(JAVA_HOME)"
# build the configured source
$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	cp -a $(SOURCE_DIR)/* $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) mvn )
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

$(BUILD_DIR)/%/.installed: $(BUILD_32)
	rm -fr $(PROTO_DIR)
	mkdir -p $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION)
	cp -r $(BUILD_DIR_32)/bin $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION)
	cp -r $(BUILD_DIR_32)/docs $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION)
	cp -r $(BUILD_DIR_32)/lib $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION)
	cp -r $(BUILD_DIR_32)/samples $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION)
	$(TOUCH) $@

build: $(BUILD_32)

install: $(INSTALL_32)

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
