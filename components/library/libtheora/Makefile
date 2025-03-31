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

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libtheora
COMPONENT_VERSION=      1.2.0
COMPONENT_SUMMARY=      Theora video compression codec
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:279327339903b544c28a92aeada7d0dcfd0397b59c2f368cc698ac56f515906e
COMPONENT_ARCHIVE_URL=  https://downloads.xiph.org/releases/theora/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.theora.org
COMPONENT_FMRI=         codec/libtheora
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE=      Xiph.org BSD-style
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-examples

# Build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += system/library
