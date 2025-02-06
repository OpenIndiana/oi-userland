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
# Copyright (c) 2024, Andreas Wacknitz
#
BUILD_BITS= 64_and_32
BUILD_STYLE= cmake
USE_DEFAULT_TEST_TRANSFORMS = yes
USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openjpeg
COMPONENT_VERSION=	2.5.3
COMPONENT_SUMMARY=	OpenJPEG library : Open source JPEG 2000 codecs
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.openjpeg.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:368fe0468228e767433c9ebdea82ad9d801a3ad1e4234421f352c8b06e7aa707
COMPONENT_ARCHIVE_URL=	https://github.com/uclouvain/openjpeg/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=     	image/library/openjpeg
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=	BSD-2-Clause
COMPONENT_LICENSE_FILE=	LICENSE

#
# The test suite requires an extra 600+ MiB download of conformance data.
#
COMPONENT_NAME_1=	openjpeg-data
GIT_REPO_1=		https://github.com/uclouvain/openjpeg-data
GIT_COMMIT_ID_1=	39524bd
GIT_HASH_1=		sha256:98cfc842a1ffb8b96862cc127b49eca6d016c5fa797fc77d7396f18b021e3671
COMPONENT_LICENSE_1=	$(COMPONENT_LICENSE)

include $(WS_MAKE_RULES)/common.mk

CFLAGS += $(CPP_LARGEFILES)

CMAKE_OPTIONS += -DCMAKE_EXE_LINKER_FLAGS:STRING="-lnsl -lsocket"
# For jar files
CMAKE_OPTIONS += -DCMAKE_INSTALL_DATAROOTDIR=$(USRSHAREDIR)/lib/java
CMAKE_OPTIONS += -DBUILD_CODEC:BOOL=ON
CMAKE_OPTIONS += -DBUILD_DOC:BOOL=OFF
CMAKE_OPTIONS += -DBUILD_JPIP:BOOL=ON
CMAKE_OPTIONS += -DBUILD_PKGCONFIG_FILES:BOOL=ON
CMAKE_OPTIONS += -DBUILD_SHARED_LIBS:BOOL=ON
CMAKE_OPTIONS += -DBUILD_STATIC_LIBS:BOOL=OFF
CMAKE_OPTIONS += -DBUILD_THIRDPARTY:BOOL=ON
CMAKE_OPTIONS += -DBUILD_TESTING:BOOL=ON
CMAKE_OPTIONS += -DOPJ_DATA_ROOT:PATH="$(BUILD_DIR_$(BITS))/../../$(COMPONENT_SRC_1)"

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRBINDIR32) ;

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
