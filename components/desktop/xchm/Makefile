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

BUILD_STYLE= configure
BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         xchm
COMPONENT_VERSION=      1.33
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      CHM viewer for UNIX
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:b3e36255136b89c7ad1385d5c1e6c0ea9a28982e5cbb22ff4b928baba04ec02a
COMPONENT_PROJECT_URL=  https://github.com/rzvncj/xCHM
COMPONENT_ARCHIVE_URL= 	$(COMPONENT_PROJECT_URL)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=
COMPONENT_CLASSIFICATION=
COMPONENT_LICENSE=		

include $(WS_MAKE_RULES)/common.mk

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/desktop/chmlib
REQUIRED_PACKAGES += library/graphics/wxwidgets-3
REQUIRED_PACKAGES += system/library
