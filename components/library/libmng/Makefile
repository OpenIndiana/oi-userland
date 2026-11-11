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
# Copyright 2019 Tim Mooney <Timothy.V.Mooney@gmail.com>
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmng
COMPONENT_VERSION=	2.0.3
COMPONENT_REVISION=	3
COMPONENT_SUMMARY=	The Multiple Image Network Graphics Library
COMPONENT_PROJECT_URL=	https://sourceforge.net/projects/libmng/
COMPONENT_DESCRIPTION=	A PNG-like image format library supporting multiple images, animations and transparent JPEG.
COMPONENT_FMRI=		library/graphics/libmng
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	MNG License (BSD-like)
COMPONENT_LICENSE_FILE=	LICENSE

COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:cf112a1fb02f5b1c0fce5cab11ea8243852c139e669c44014125874b14b7dfaa
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/libmng/files/libmng-devel/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# because Solaris installed the lcms headers elsewhere
CFLAGS += `pkg-config --cflags lcms2`
# because it's unclear that --enable-largefile works properly
CFLAGS += $(CPP_LARGEFILES)

# build with the distribution default libjpeg
CFLAGS            +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS          +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS           +=    $(JPEG_LDFLAGS)

CONFIGURE_OPTIONS += --includedir=$(USRINCDIR)/libmng
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
CONFIGURE_OPTIONS += --with-lcms2
CONFIGURE_OPTIONS += --with-zlib
CONFIGURE_OPTIONS += --with-jpeg

# distclean target was not run before the tarball was generated
COMPONENT_PREP_ACTION = \
	( cd $(@D) ; rm -f config.log config.status libmng.pc ; PATH="$(PATH)" ./bootstrap.sh )

PKG_PROTO_DIRS += $(USERLAND_ARCHIVES)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
