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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libmng
COMPONENT_VERSION=	1.0.10
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:78ad516a1de79d00de720bf2a7c9afea2c896b09
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/libmng/files/libmng-devel/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_1 =	mng-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_HASH_1 = sha1:074c31b6f6f7c8ee98b4f0b893dfefcba6fd926f
COMPONENT_ARCHIVE_URL_1 = http://www.libpng.org/pub/mng/spec/mng-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_2 =	mng-lc-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_HASH_2 = sha1:42f01c79cfbd226a9d4b327017e49b5fd4856f94
COMPONENT_ARCHIVE_URL_2 = http://www.libpng.org/pub/mng/spec/mng-lc-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_3 =	mng-vlc-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_HASH_3 = sha1:906c1db4ff9efc3f36b913651c6e9b05256d25ec
COMPONENT_ARCHIVE_URL_3 = http://www.libpng.org/pub/mng/spec/mng-vlc-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_4 =	jng-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_HASH_4 = sha1:b5a036d6249ebbbad04e80bd7d203cbb5b31f0de
COMPONENT_ARCHIVE_URL_4 = http://www.libpng.org/pub/mng/spec/jng-1.0-20010209-pdg.html
COMPONENT_ARCHIVE_5 =	index.html
COMPONENT_ARCHIVE_HASH_5 = sha1:074c31b6f6f7c8ee98b4f0b893dfefcba6fd926f
COMPONENT_ARCHIVE_URL_5 = http://www.libpng.org/pub/mng/spec/index.html

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk
include ../../make-rules/lint-libraries.mk

# because Solaris installed the lcms headers elsewhere
CFLAGS += `pkg-config --cflags lcms`
# because it's unclear that --enable-largefile works properly
CFLAGS += $(CPP_LARGEFILES)

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"

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
		    libtoolize --force --copy ; aclocal-1.10 ; \
		    automake-1.10 --add-missing --copy ; autoconf )

$(BUILD_DIR)/libmng-64.pc:	Solaris/libmng-64.pc
	/bin/sed -e "s#MACH64#$(MACH64)#g" <$< >$@

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64) $(BUILD_DIR)/libmng-64.pc

test:	$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk

