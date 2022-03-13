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

BUILD_BITS=		64
BUILD_STYLE=	justmake

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		jxrlib
COMPONENT_VERSION=	0.2.4
COMPONENT_SUMMARY=	Decode and encode JPEG-XR data from Java
COMPONENT_PROJECT_URL=	https://github.com/glencoesoftware/jxrlib
COMPONENT_FMRI=		library/jxlib
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_URL=	https://github.com/glencoesoftware/$(COMPONENT_NAME)/archive/refs/tags/v$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH=	sha256:aef05b75f33551baf03373e13011ca25623632cfe6079b2d0ea32f4535e72b75
COMPONENT_LICENSE=	BSD 2-Clause
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)
COMPONENT_POST_UNPACK_ACTION=mkdir -p garbagecollector; \
							 echo \<settings\>\<localRepository\>$(SOURCE_DIR)\/..\/garbagecollector\/Repository\<\/localRepository\>\<\/settings\> > "$(SOURCE_DIR)/../garbagecollector/settings.xml"; \
							 sed 's|DIR_INSTALL|PREFIX|g' -i $(SOURCE_DIR)/libjxr.pc.in; \
							 sed 's|"DIR_INSTALL": "$(DIR_INSTALL)"|"PREFIX": "$(PREFIX)"|g' -i $(SOURCE_DIR)/Makefile
COMPONENT_BUILD_GMAKE_ARGS+=SHARED=1
COMPONENT_BUILD_GMAKE_ARGS+=PREFIX=/usr
COMPONENT_BUILD_GMAKE_ARGS+=swig all
COMPONENT_BUILD_GMAKE_ARGS+=CC="$(CC) $(CFLAGS)"
COMPONENT_BUILD_GMAKE_ARGS+=CXX="$(CXX) $(CXXFLAGS)"
COMPONENT_PRE_INSTALL_ACTION=LD_LIBRARY_PATH="$(SOURCE_DIR)/../build/amd64/build" mvn -s "$(SOURCE_DIR)/../garbagecollector/settings.xml" -f $(SOURCE_DIR)/../build/amd64/java package
COMPONENT_INSTALL_ARGS+=SHARED=1
COMPONENT_INSTALL_ARGS+=DIR_INSTALL=$(SOURCE_DIR)/../build/prototype/i386/

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
