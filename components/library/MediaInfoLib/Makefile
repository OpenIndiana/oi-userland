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
#

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		MediaInfoLib
COMPONENT_VERSION=	21.09
IPS_COMPONENT_VERSION=	21.9
HUMAN_VERSION= $(COMPONENT_VERSION)
COMPONENT_SUMMARY=	MediaInfo(Lib) is a convenient unified display of the most relevant technical and tag data for video and audio files.
COMPONENT_PROJECT_URL=	https://github.com/MediaArea/MediaInfoLib
COMPONENT_FMRI=		library/libmediainfo
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/MediaArea/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:6db61bef0ad5b126d17bb59210c240f33fafb3450946e7b114d7884abf6e99fb
COMPONENT_LICENSE=	BSD 2-Clause
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION=	( cd $(SOURCE_DIR)/Project/GNU/Library/ && ./autogen.sh; )
CONFIGURE_SCRIPT =	$(SOURCE_DIR)/Project/GNU/Library/configure

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+= "builddir=$(SOURCE_DIR)/../build/amd64"
CONFIGURE_ENV += CPPFLAGS="$(CXXFLAGS) -DUNICODE -I/usr/include -DMEDIAINFO_GRAPHVIZ_NO -DMEDIAINFO_LIBCURL_NO -DMEDIAINFO_LIBMMS_NO -I$(SOURCE_DIR)/Source/ThirdParty/aes-gladman -I$(SOURCE_DIR)/Source/ThirdParty/md5 -I$(SOURCE_DIR)/Source/ThirdParty/sha1-gladman -I$(SOURCE_DIR)/Source/ThirdParty/sha2-gladman -I$(SOURCE_DIR)/Source/ThirdParty/hmac-gladman -I$(SOURCE_DIR)/Source/ThirdParty/tinyxml2 -I$(SOURCE_DIR)/Source/ThirdParty/base64 -DUNICODE -fPIC -O2"
CFLAGS+=-I$(SOURCE_DIR)/Source/ThirdParty/aes-gladman -I$(SOURCE_DIR)/Source/ThirdParty/md5 -I$(SOURCE_DIR)/Source/ThirdParty/sha1-gladman -I$(SOURCE_DIR)/Source/ThirdParty/sha2-gladman -I$(SOURCE_DIR)/Source/ThirdParty/hmac-gladman -fPIC -O2
CXXFLAGS+=-DUNICODE -DSIZE_T_IS_LONG -DMEDIAINFO_GRAPHVIZ_NO -DMEDIAINFO_LIBCURL_NO -DMEDIAINFO_LIBMMS_NO -I$(SOURCE_DIR)/Source/ThirdParty/aes-gladman -I$(SOURCE_DIR)/Source/ThirdParty/md5 -I$(SOURCE_DIR)/Source/ThirdParty/sha1-gladman -I$(SOURCE_DIR)/Source/ThirdParty/sha2-gladman -I$(SOURCE_DIR)/Source/ThirdParty/hmac-gladman -I$(SOURCE_DIR)/Source/ThirdParty/tinyxml2 -I$(SOURCE_DIR)/Source/ThirdParty/base64 -DUNICODE -fPIC -O2

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libzen
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
