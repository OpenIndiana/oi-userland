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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xchm

COMPONENT_VERSION= 1.23
COMPONENT_SUMMARY= CHM viewer for UNIX
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:8f8f5c60954f340e50f1613913eaca6ff489c10ca36b2570b360d8ccba77c062
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/xchm/files/xCHM/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://xchm.sourceforge.net/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Missing files in build dir for configure without this.
# COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D)) 

build: $(BUILD_32)

install: $(INSTALL_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/chmlib
REQUIRED_PACKAGES += library/graphics/wxwidgets
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
