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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2018 Harry Liebel <hliebel@gmail.com>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmng
COMPONENT_VERSION=	1.0.10
COMPONENT_REVISION=	3
COMPONENT_FMRI=		library/graphics/libmng
COMPONENT_PROJECT_URL=	http://www.libpng.org/pub/mng
COMPONENT_SUMMARY=	The Multiple Image Network Graphics Library
COMPONENT_DESCRIPTION=	A PNG-like image format library supporting multiple images, animations and transparent JPEG.
COMPONENT_LICENSE=	MNG License (BSD-like)
COMPONENT_CLASSIFICATION= System/Libraries

COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:03a79dac9b9316d37227057614a248a946f997c4d1a3437fb569e9a63897f911
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/libmng/files/libmng-devel/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_1 =	mng-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_HASH_1 = \
    sha256:fe8e0a7aa7371c4c1369b56485fdbd96699e53f0078d7369162c883bb7dac1ca
COMPONENT_ARCHIVE_URL_1 = http://www.libpng.org/pub/mng/spec/mng-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_2 =	mng-lc-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_HASH_2 = \
    sha256:6b6a463b50e38e89006c68e629444a6154d70ee34f5d64056c4910346a07b623
COMPONENT_ARCHIVE_URL_2 = http://www.libpng.org/pub/mng/spec/mng-lc-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_3 =	mng-vlc-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_HASH_3 = \
    sha256:77340f6f922c8c2daf2cc120812bbebb26c825e4a08c3c8be6567ef8c34e2ad0
COMPONENT_ARCHIVE_URL_3 = http://www.libpng.org/pub/mng/spec/mng-vlc-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_4 =	jng-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_HASH_4 = \
    sha256:9e5f458dadfdc32bce34dd005f76ee3592cf2cea79d6100691a5d20603f54d05
COMPONENT_ARCHIVE_URL_4 = http://www.libpng.org/pub/mng/spec/jng-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_5 =	index.html
COMPONENT_ARCHIVE_HASH_5 = \
    sha256:fe8e0a7aa7371c4c1369b56485fdbd96699e53f0078d7369162c883bb7dac1ca
COMPONENT_ARCHIVE_URL_5 = http://www.libpng.org/pub/mng/spec/index.html


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# because Solaris installed the lcms headers elsewhere
CFLAGS += `pkg-config --cflags lcms2`
# because it's unclear that --enable-largefile works properly
CFLAGS += $(CPP_LARGEFILES)

CONFIGURE_OPTIONS += --includedir=/usr/include/libmng
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --enable-shared 
CONFIGURE_OPTIONS += --disable-static 
CONFIGURE_OPTIONS += --disable-libtool-lock 
CONFIGURE_OPTIONS += --enable-largefile 
CONFIGURE_OPTIONS += --enable-buildso 
CONFIGURE_OPTIONS += --enable-read 
CONFIGURE_OPTIONS += --enable-write 
CONFIGURE_OPTIONS += --enable-display 
CONFIGURE_OPTIONS += --enable-dynamic 
CONFIGURE_OPTIONS += --enable-chunks 
CONFIGURE_OPTIONS += --enable-storechunks 
CONFIGURE_OPTIONS += --with-lcms
CONFIGURE_OPTIONS += --with-zlib
CONFIGURE_OPTIONS += --with-jpeg

COMPONENT_PREP_ACTION = \
	( cd $(@D) ; \
	    $(CP) makefiles/configure.in makefiles/Makefile.am . ; \
		    libtoolize --force --copy ; aclocal ; \
		    automake --add-missing --copy ; autoconf )

PKG_PROTO_DIRS += $(USERLAND_ARCHIVES)

$(BUILD_DIR)/libmng-64.pc:	Solaris/libmng-64.pc
	/bin/sed -e "s#MACH64#$(MACH64)#g" <$< >$@

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64) $(BUILD_DIR)/libmng-64.pc

test:	$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
