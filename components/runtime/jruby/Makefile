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
COMPONENT_VERSION= 	9.1.15.0
COMPONENT_SUMMARY= 	Java implementation of the Ruby programming language
COMPONENT_FMRI = 	runtime/java/jruby
COMPONENT_CLASSIFICATION = Development/Ruby
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_NAME)-src-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:0377389ede58d4b23a1fff3877f29d0043ecb509630e94d800c25136320966d5
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
	gfind $(PROTO_DIR) -regextype posix-extended -regex '.*\.(bat|dll|exe)' -print -delete; \
	rm -r $(PROTO_DIR)/usr/jruby/$(COMPONENT_VERSION)/lib/jni/{Darwin,*-Linux,*-Windows,*-AIX,*-*BSD}

build: $(BUILD_32)

install: $(INSTALL_32)

# Build dependencies
REQUIRED_PACKAGES += runtime/ruby-22

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
