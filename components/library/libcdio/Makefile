#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
# Copyright 2022 Niklas Poslovski
# Copyright 2025 Klaus Ziegler
#

BUILD_STYLE=configure
BUILD_BITS=64_and_32
USE_PARALLEL_BUILD = yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libcdio
COMPONENT_VERSION=      2.2.0
COMPONENT_PROJECT_URL=  https://github.com/libcdio/libcdio
COMPONENT_SUMMARY=      GNU Compact Disc Input and Control Library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
	sha256:6f8fbdf4d189cf63f2a7a1549c516cd720c7b222c7aaadbc924a26e745a48539
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/releases/download/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_FMRI=         library/audio/libcdio

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CPPFLAGS += -I/usr/include/dbus-1.0 -I/usr/lib/dbus-1.0/include -I/usr/include/ncurses

LDFLAGS += -lhal -ldbus-1

CONFIGURE_OPTIONS+=	--disable-static

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# make gcc-14 happy and include alloca.h
COMPONENT_POST_CONFIGURE_ACTION += ( \
	cd $(COMPONENT_SRC); \
	$(GSED) -i -e '/e <stdio/a \#include <alloca.h>' src/getopt.c );

COMPONENT_POST_CONFIGURE_ACTION += ( \
	cd $(@D); \
	$(GSED) -i -e 's/_FILE_OFFSET_BITS 64/_FILE_OFFSET_BITS 32/' config.h );


COMPONENT_POST_INSTALL_ACTION= \
	(cd $(PROTOUSRDIR) ;  $(MV) include/cdio/cdio_config.h include/cdio/cdio_config-$(BITS).h )

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/audio/libcddb
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus/32
