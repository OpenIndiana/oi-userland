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
# Copyright 2022 Andreas Wacknitz
#

BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= qpdf
COMPONENT_VERSION= 12.0.0
COMPONENT_SUMMARY= QPDF is a command-line program that does structural, content-preserving transformations on PDF files
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:7380fe9d5b612a6c912cbf3a5875d9e27c20db6c559ebca51360da5125f351b8
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/qpdf/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://qpdf.sourceforge.net/
COMPONENT_FMRI= print/qpdf
COMPONENT_CLASSIFICATION= System/Printing
COMPONENT_LICENSE=      Artistic 2.0
COMPONENT_LICENSE_FILE= Artistic-2.0

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release
CMAKE_OPTIONS += -DBUILD_STATIC_LIBS=OFF

# Manually added dependencies
# qpdf on SPARC needs math library
ifeq ($(strip $(MACH)),sparc)
REQUIRED_PACKAGES += system/library/math
endif

# libqpdf.so seems to depend on them but they are not properly detected (why?):
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/desktop/p11-kit
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libidn2
REQUIRED_PACKAGES += library/libtasn1
REQUIRED_PACKAGES += library/libunistring
REQUIRED_PACKAGES += library/nettle

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
