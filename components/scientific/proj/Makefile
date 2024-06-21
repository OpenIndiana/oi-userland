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
# Copyright (c) 2023 Andreas Wacknitz
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	        proj
COMPONENT_VERSION=      9.4.1
COMPONENT_SUMMARY=      PROJ is a generic coordinate transformation software that transforms geospatial coordinates from \
	one coordinate reference system (CRS) to another
COMPONENT_PROJECT_URL=  https://proj.org/
COMPONENT_SRC=	        $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://download.osgeo.org/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:ffe20170ee2b952207adf8a195e2141eab12cda181e49fdeb54425d98c7171d7
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE=	COPYING

COMPONENT_ARCHIVE_1=		proj-data-1.18.tar.gz
COMPONENT_ARCHIVE_URL_1=	https://download.osgeo.org/proj/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1=	sha256:bc18bfe967f51eb05bb2fd61cb7045548d992d20842d2c38f4cbc37d904dfd50

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
