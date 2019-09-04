#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2013-2016, Aurelien Larcher. All rights reserved.
# Copyright (c) 2019, Tim Mooney
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openjpeg
COMPONENT_SUMMARY=	OpenJPEG library : Open source JPEG 2000 codecs
COMPONENT_VERSION=	2.3.1
COMPONENT_FMRI=     	image/library/openjpeg
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.openjpeg.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:63f5a4713ecafc86de51bfad89cc07bb788e9bba24ebbf0c4ca637621aadb6a9
COMPONENT_ARCHIVE_URL=	https://github.com/uclouvain/openjpeg/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

#
# the test suite requires an extra 600+ MiB download of conformance data.
# if you want to include the conformance data, you need to uncomment
# the COMPONENT_*_1 lines, below:
#
#COMPONENT_NAME_1=	openjpeg-data
#COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-master
#COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).zip
#COMPONENT_ARCHIVE_URL_1=https://github.com/uclouvain/$(COMPONENT_NAME_1)/archive/master.zip
#COMPONENT_ARCHIVE_HASH_1= \
#	sha256:88cec290f19318785f2b6804e28523f6ae119fdd0c17c9867e9966c68d9461f0
#COMPONENT_LICENSE_1=	$(COMPONENT_LICENSE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/cmake.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS+= -std=c99 -D_XOPEN_SOURCE=600
CFLAGS+= $(CPP_LARGEFILES)

CMAKE_OPTIONS+= -DCMAKE_EXE_LINKER_FLAGS:STRING="-lnsl -lsocket"
# Openjpeg does not use CMake's internal variables.
CMAKE_OPTIONS+=	-DOPENJPEG_INSTALL_BIN_DIR=$(CMAKE_BINDIR.$(BITS))
CMAKE_OPTIONS+=	-DOPENJPEG_INSTALL_LIB_DIR=$(CMAKE_LIBDIR.$(BITS))
# For jar files
CMAKE_OPTIONS+=	-DOPENJPEG_INSTALL_SHARE_DIR=$(USRSHAREDIR)/lib/java
CMAKE_OPTIONS+= -DBUILD_CODEC:BOOL=ON
CMAKE_OPTIONS+= -DBUILD_DOC:BOOL=OFF
CMAKE_OPTIONS+= -DBUILD_JPIP:BOOL=ON
CMAKE_OPTIONS+= -DBUILD_JPWL:BOOL=ON
CMAKE_OPTIONS+= -DBUILD_MJ2:BOOL=ON
CMAKE_OPTIONS+= -DBUILD_PKGCONFIG_FILES:BOOL=ON
CMAKE_OPTIONS+= -DBUILD_SHARED_LIBS:BOOL=ON
CMAKE_OPTIONS+= -DBUILD_THIRDPARTY:BOOL=ON   
# default: no tests:
CMAKE_OPTIONS+= -DBUILD_TESTING:BOOL=OFF
#
# if you've uncommented the COMPONENT_*_1 settings, above, to download
# the conformance data, then you can enable the test suite by uncommenting
# the next two lines:
#
#CMAKE_OPTIONS+= -DBUILD_TESTING:BOOL=ON
#CMAKE_OPTIONS+= -DOPJ_DATA_ROOT:PATH="$(BUILD_DIR_$(BITS))/../../$(COMPONENT_SRC_1)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# default: no tests
test: $(NO_TESTS)

# if you've enabled the COMPONENT_*_1 and uncommented the CMAKE_OPTIONS to
# BUILD_TESTING and set OPJ_DATA_ROOT, then to run the test suite:
#test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
