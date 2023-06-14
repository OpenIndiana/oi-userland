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
# Copyright 2022, Niklas Poslovski
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		FreeImage
COMPONENT_VERSION_MAJOR=3
COMPONENT_VERSION_MINOR=18
COMPONENT_VERSION_PATCH=0
COMPONENT_VERSION=	$(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR).$(COMPONENT_VERSION_PATCH)
COMPONENT_REVISION=	10
COMPONENT_SUMMARY=	A library project for developers to support popular graphics image formats
COMPONENT_PROJECT_URL=	https://freeimage.sourceforge.io
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)$(COMPONENT_VERSION_MAJOR)$(COMPONENT_VERSION_MINOR)$(COMPONENT_VERSION_PATCH).zip
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/freeimage/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:f41379682f9ada94ea7b34fe86bf9ee00935a3147be41b6569c9605a53e438fd
COMPONENT_FMRI=		library/libfreeimage
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	license-gplv3.txt

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

LDFLAGS += -L/usr/lib/$(MACH64) -ljpegxr
COMPONENT_POST_UNPACK_ACTION= \
	cp $(SOURCE_DIR)/../libfreeimage.pc $(SOURCE_DIR)/ ;\
	dos2unix $(SOURCE_DIR)/FreeImage.2013.vcxproj $(SOURCE_DIR)/FreeImage.2013.vcxproj_bak ;\
	iconv -f 8859-15 -t UTF-8 $(SOURCE_DIR)/FreeImage.2013.vcxproj_bak > $(SOURCE_DIR)/FreeImage.2013.vcxproj ;\
	echo "\n" >> $(SOURCE_DIR)/FreeImage.2013.vcxproj
	
COMPONENT_COPY_ACTION = cp $(SOURCE_DIR)/Source/LibJPEG/transupp.h $(SOURCE_DIR)/Dist/ && rm -r $(SOURCE_DIR)/Source/Lib* $(SOURCE_DIR)/Source/ZLib $(SOURCE_DIR)/Source/OpenEXR &&  cp -r $(SOURCE_DIR)/* $(@D)
COMPONENT_PRE_BUILD_ACTION = \
	echo -n "SRC" test ;\
	chmod +x $(@D)/gensrclist.sh;\
	chmod +x $(@D)/genfipsrclist.sh;\
	cd $(@D) && ./gensrclist.sh ;\
	cd $(@D) && ./genfipsrclist.sh ;\
	$(GSED) -i -e "s@MACH64@$(MACH64)@" $(@D)/Makefile.gnu
COMPONENT_BUILD_GMAKE_ARGS="file=Makefile.gnu"

FIFLAGS= -fPIC
FIFLAGS += -fexceptions
FIFLAGS += -fvisibility=default
CFLAGS += $(FIFLAGS)
CXXFLAGS += $(FIFLAGS)
CXXFLAGS += -Wno-ctor-dtor-privacy

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libraw
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/imath
REQUIRED_PACKAGES += library/jxrlib
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/openexr
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
