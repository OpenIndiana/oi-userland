#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2019 Michal Nowak
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libheif
COMPONENT_VERSION=	1.19.7
COMPONENT_SUMMARY=      libheif is an ISO/IEC 23008-12:2017 HEIF and AVIF (AV1 Image File Format) file format decoder and encoder
COMPONENT_PROJECT_URL=  https://github.com/strukturag/$(COMPONENT_NAME)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:161c042d2102665fcee3ded851c78a0eb5f2d4bfe39fba48ba6e588fd6e964f3
COMPONENT_FMRI=         library/video/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE=	LGPL-3
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(XPG6MODE)

CMAKE_OPTIONS += -DWITH_LIBDE265_PLUGIN=ON
CMAKE_OPTIONS += -DWITH_X265_PLUGIN=ON
CMAKE_OPTIONS += -DWITH_DAV1D=ON
CMAKE_OPTIONS += -DWITH_JPEG_DECODER=ON
CMAKE_OPTIONS += -DWITH_UNCOMPRESSED_CODEC=ON

# Manually added build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += codec/dav1d
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/video/libde265
REQUIRED_PACKAGES += library/video/x265
REQUIRED_PACKAGES += library/video/x265-41
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
