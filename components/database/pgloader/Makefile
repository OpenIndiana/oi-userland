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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pgloader
COMPONENT_VERSION= 	3.3.0.50
COMPONENT_SUMMARY= 	Data loading tool for PostgreSQL
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:9b6505278839a706afb7017e0a59fdb6b43fc58aafe4685aacf7f4beb2fa128f
COMPONENT_ARCHIVE_URL= \
  https://github.com/dimitri/pgloader/archive/v$(COMPONENT_VERSION).zip
COMPONENT_PROJECT_URL = http://pgloader.io/

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ARGS=

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
	$(MKDIR) $(PROTO_DIR)/usr/bin \
		$(PROTO_DIR)/usr/share/doc/pgloader \
		$(PROTO_DIR)/usr/share/man/man1
	cp $(BUILD_DIR_32)/build/bin/pgloader $(PROTO_DIR)/usr/bin/pgloader
	cp $(BUILD_DIR_32)/TODO.md $(BUILD_DIR_32)/README.md $(PROTO_DIR)/usr/share/doc/pgloader
	cp $(BUILD_DIR_32)/pgloader.1 $(PROTO_DIR)/usr/share/man/man1
	$(TOUCH) $@

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR)

# Build dependencies
REQUIRED_PACKAGES += library/freetds
REQUIRED_PACKAGES += runtime/sbcl

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
