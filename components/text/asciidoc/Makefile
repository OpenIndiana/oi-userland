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

COMPONENT_NAME= 	asciidoc
COMPONENT_VERSION= 	8.6.10
COMPONENT_SUMMARY= 	Text based document generation tool
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:9e52f8578d891beaef25730a92a6e723596ddbd07bfe0d2a56486fcf63a0b983
COMPONENT_ARCHIVE_URL= \
  https://github.com/asciidoc/asciidoc/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL = http://www.methods.co.nz/asciidoc/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(@D); autoreconf -vif )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CP) -a  $(SOURCE_DIR)/* $(@D))

CONFIGURE_OPTIONS +=  --sysconfdir=/etc

CONFIGURE_ENV += PYTHON=$(PYTHON)

build: $(BUILD_32)

install: $(INSTALL_32)

REQUIRED_PACKAGES += runtime/python-27
