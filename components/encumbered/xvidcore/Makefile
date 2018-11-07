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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xvidcore
COMPONENT_VERSION= 1.3.5
COMPONENT_FMRI = library/video/xvid
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SUMMARY= ISO MPEG-4 compliant video codec
COMPONENT_SRC= $(COMPONENT_NAME)
COMPONENT_ARCHIVE= $(COMPONENT_SRC)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:165ba6a2a447a8375f7b06db5a3c91810181f2898166e7c8137401d7fc894cf0
COMPONENT_ARCHIVE_URL= \
  http://downloads.xvid.org/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.xvid.com/
COMPONENT_LICENSE = GPLv2.0
COMPONENT_LICENSE_FILE = LICENSE

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = $(PATH.gnu)

COMPONENT_PREP_ACTION += ( cd $(COMPONENT_SRC)/build/generic && $(CONFIG_SHELL) bootstrap.sh)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS.32 = --enable-assembly
CONFIGURE_OPTIONS.64 = --disable-assembly
CONFIGURE_OPTIONS += $(CONGIGURE_OPTIONS.$(BITS))

CONFIGURE_SCRIPT = $(@D)/build/generic/configure

$(BUILD_DIR)/%/.configured:     $(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(@D)/build/generic ; $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) \
	        $(CONFIGURE_SCRIPT) $(CONFIGURE_OPTIONS))
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@

COMPONENT_BUILD_ARGS += -C $(@D)/build/generic
COMPONENT_INSTALL_ARGS += -C $(@D)/build/generic

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
