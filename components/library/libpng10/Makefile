#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
#

BUILD_BITS= 32_and_64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libpng
COMPONENT_VERSION=      1.0.69
COMPONENT_REVISION=     2
COMPONENT_PROJECT_URL=  http://www.libpng.org/
COMPONENT_SUMMARY=      Portable Network Graphics library version $(COMPONENT_VERSION)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:775798fd8e82c8dfe2b3e7d7bff3fd53d4ee875be65246f98bbb56fa4c1ed842
COMPONENT_ARCHIVE_URL=  https://sourceforge.net/projects/libpng/files/libpng10/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=         image/library/libpng10
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE=      libpng
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-static

# for tests to pass
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
