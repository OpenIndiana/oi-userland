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

COMPONENT_NAME= liblouis
COMPONENT_VERSION= 2.1.1
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= Support for contracted braille
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_NAME)_2_1_1
COMPONENT_ARCHIVE= $(COMPONENT_NAME)_2_1_1.tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:1346de8a755781fb645c705b587f21f694cc7e8f9c4b7a01441d30c8e0be25a4
COMPONENT_ARCHIVE_URL= \
  https://github.com/liblouis/liblouis/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://liblouis.org/
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = library/liblouis
COMPONENT_LICENSE = LGPLv3,GPLv3
COMPONENT_LICENSE_FILE = liblouis.license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_BUILD_ARGS =

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i ) 

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ( cp -a $(SOURCE_DIR)/* $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-ucs4

CONFIGURE_ENV += PYTHON=$(PYTHON)

ENV = /usr/bin/env -i

$(BUILD_DIR)/.built_python_modules:	$(INSTALL_32)
	cd $(BUILD_DIR_32)/python && $(ENV) LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib:/usr/lib:/lib $(PYTHON) setup.py build
	$(TOUCH) $@

$(BUILD_DIR)/.installed_python_modules:	$(INSTALL_32) $(BUILD_DIR)/.built_python_modules
	cd $(BUILD_DIR_32)/python && $(ENV) LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib:/usr/lib:/lib $(PYTHON) setup.py install --root $(PROTO_DIR) --install-lib /usr/lib/python$(PYTHON_VERSION)/vendor-packages
	$(TOUCH) $@

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64) $(BUILD_DIR)/.built_python_modules $(BUILD_DIR)/.installed_python_modules

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
