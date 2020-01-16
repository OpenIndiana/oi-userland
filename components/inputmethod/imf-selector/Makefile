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
# Copyright 2015 Alexander Pyhalov
#

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= imf-selector
COMPONENT_VERSION= 0.5.11
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= Input Method Framework startup
COMPONENT_SRC = src
COMPONENT_PROJECT_URL = http://www.openindiana.org
COMPONENT_FMRI = system/input-method/imf-startup
COMPONENT_LICENSE_FILE = OPENSOLARIS.LICENSE
COMPONENT_LICENSE = CDDL
COMPONENT_CLASSIFICATION = System/Internationalization

TEST_TARGET = $(NO_TESTS)
PYTHON_VERSION = 3.5
include $(WS_MAKE_RULES)/common.mk

clobber:: clean

$(SOURCE_DIR)/.prep:	Makefile
	$(TOUCH) $@

PATH=$(PATH.gnu)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D))

CONFIGURE_SCRIPT = $(@D)/autogen.sh

CONFIGURE_OPTIONS += --sysconfdir=/etc

CONFIGURE_ENV += PYTHON=$(PYTHON)

clean::
	$(RM) $(SOURCE_DIR)/.prep
	$(RM) -rf $(BUILD_DIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/pygobject-3-35
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += SUNWcs
