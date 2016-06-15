#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS = 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openjpeg
COMPONENT_VERSION=	2.1.0
COMPONENT_PROJECT_URL=	http://www.openjpeg.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-version.2.1
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:4afc996cd5e0d16360d71c58216950bcb4ce29a3272360eb29cadb1c8bce4efc
COMPONENT_ARCHIVE_URL=	https://github.com/uclouvain/$(COMPONENT_NAME)/archive/version.2.1.tar.gz
COMPONENT_BUGDB=	library/openjpeg

TPNO=			18449

BUILD_STYLE = cmake

# Requires images from an external source
TEST_TARGET = $(SKIP_TEST)

include $(WS_MAKE_RULES)/common.mk

# Workaround non-standard type usage in big endian builds.
CFLAGS.studio.sparc += -Du_int16_t=uint16_t

CMAKE_OPTIONS += -DOPENJPEG_INSTALL_BIN_DIR=$(USRBIN)
CMAKE_OPTIONS += -DOPENJPEG_INSTALL_LIB_DIR=$(USRLIB)
CMAKE_OPTIONS += -DCMAKE_VERBOSE_MAKEFILE=ON
CMAKE_OPTIONS += -DLCMS2_INCLUDE_DIR=$(USRINCDIR)/lcms

REQUIRED_PACKAGES += developer/build/cmake
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += system/library/math
