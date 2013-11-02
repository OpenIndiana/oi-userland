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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pgloader
COMPONENT_VERSION= 	2.3.1
COMPONENT_SUMMARY= 	pgBouncer connection pooler
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_COMMIT)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).zip
COMPONENT_COMMIT=	c603221ae0948d02580e6fcfddfa90f3e6d2e6b0
COMPONENT_ARCHIVE_HASH= \
  sha256:acc852c9f616ca4e5e9add3a12691fc55847ef16fcf47065d13e495927f11385
COMPONENT_ARCHIVE_URL= \
  https://github.com/dimitri/pgloader/archive/$(COMPONENT_COMMIT).zip
COMPONENT_PROJECT_URL = http://tapoueh.org/pgsql/pgloader.html

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_BUILD_TARGETS=	doc

$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CP) -a $(SOURCE_DIR)/* $(@D)
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; $(ENV) $(COMPONENT_BUILD_ENV) \
	$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_BUILD_ARGS) \
		$(COMPONENT_BUILD_TARGETS))
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

build: $(BUILD_32)

install: $(INSTALL_32)

$(BUILD_DIR)/%/.installed: $(BUILD_32)
	$(MKDIR) $(PROTO_DIR)/usr/bin $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/pgloader \
		$(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/reformat $(PROTO_DIR)/usr/share/doc/pgloader \
		$(PROTO_DIR)/usr/share/man/man1
	cp $(BUILD_DIR_32)/pgloader.py $(PROTO_DIR)/usr/bin/pgloader
	cp $(BUILD_DIR_32)/pgloader/*.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/pgloader/
	cp $(BUILD_DIR_32)/reformat/*.py $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/reformat/
	cp -a $(BUILD_DIR_32)/examples $(PROTO_DIR)/usr/share/doc/pgloader
	cp $(BUILD_DIR_32)/TODO.txt $(BUILD_DIR_32)/BUGS.txt $(PROTO_DIR)/usr/share/doc/pgloader
	cp $(BUILD_DIR_32)/pgloader.1 $(PROTO_DIR)/usr/share/man/man1

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)
