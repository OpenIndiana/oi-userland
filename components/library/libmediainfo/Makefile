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
# Copyright 2022, Daniel Chan
# Copyright 2023, Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		MediaInfoLib
COMPONENT_VERSION=	23.4
HUMAN_VERSION=		23.04
COMPONENT_SUMMARY=	MediaInfo(Lib) is a convenient unified display of the most relevant technical and tag data for video and audio files.
COMPONENT_PROJECT_URL=	https://github.com/MediaArea/$(COMPONENT_NAME)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:afcbab2f849952d8e5ec9c4887db110b6f4d22f592ab6d8787232e9ef93c6fbb
COMPONENT_FMRI=		library/libmediainfo
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=	BSD 2-Clause
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION= ( cp -Rp $(SOURCE_DIR)/* $(@D) && \
	cd $(@D)/Project/GNU/Library/ && ./autogen.sh; )

CONFIGURE_SCRIPT= $(@D)/Project/GNU/Library/configure

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-libcurl
CONFIGURE_OPTIONS += --with-libmms
CONFIGURE_OPTIONS += --with-graphviz
CONFIGURE_OPTIONS += "builddir=$(SOURCE_DIR)/../build/amd64"
CONFIGURE_ENV += CPPFLAGS="$(CXXFLAGS) -DUNICODE -I/usr/include -DMEDIAINFO_GRAPHVIZ_NO -DMEDIAINFO_LIBCURL_NO -DMEDIAINFO_LIBMMS_NO -I$(SOURCE_DIR)/Source/ThirdParty/aes-gladman -I$(SOURCE_DIR)/Source/ThirdParty/md5 -I$(SOURCE_DIR)/Source/ThirdParty/sha1-gladman -I$(SOURCE_DIR)/Source/ThirdParty/sha2-gladman -I$(SOURCE_DIR)/Source/ThirdParty/hmac-gladman -I$(SOURCE_DIR)/Source/ThirdParty/tinyxml2 -I$(SOURCE_DIR)/Source/ThirdParty/base64 -DUNICODE -fPIC -O2"
CFLAGSi += -I$(SOURCE_DIR)/Source/ThirdParty/aes-gladman -I$(SOURCE_DIR)/Source/ThirdParty/md5 -I$(SOURCE_DIR)/Source/ThirdParty/sha1-gladman -I$(SOURCE_DIR)/Source/ThirdParty/sha2-gladman -I$(SOURCE_DIR)/Source/ThirdParty/hmac-gladman -fPIC -O2
CXXFLAGS += -DUNICODE -DSIZE_T_IS_LONG -I$(SOURCE_DIR)/Source/ThirdParty/aes-gladman -I$(SOURCE_DIR)/Source/ThirdParty/md5 -I$(SOURCE_DIR)/Source/ThirdParty/sha1-gladman -I$(SOURCE_DIR)/Source/ThirdParty/sha2-gladman -I$(SOURCE_DIR)/Source/ThirdParty/hmac-gladman -I$(SOURCE_DIR)/Source/ThirdParty/tinyxml2 -I$(SOURCE_DIR)/Source/ThirdParty/base64 -DUNICODE -fPIC -O2

# Copy test scripts into test folder and change PATH_SCRIPT=$(dirname $0) to PATH_SCRIPT="../build/amd64/test/"
COMPONENT_PRE_TEST_ACTION= ( \
	cp -Rp $(SOURCE_DIR)/Project/GNU/Library/test/* $(@D)/test/ && \
	$(GSED) -i -e 's;PATH_SCRIPT=$$(dirname \"$$0\");PATH_SCRIPT=\"$(@D)/test\";' $(@D)/test/*.sh && \
	chmod 755 $(@D)/test/*.sh )

# clone_regression_files target clones the test data
COMPONENT_TEST_TARGETS= clone_regression_files check

unexport SHELLOPTS

# Manually added dependencies
REQUIRED_PACKAGES += image/graphviz
REQUIRED_PACKAGES += library/video/libmms
REQUIRED_PACKAGES += web/curl

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libzen
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
