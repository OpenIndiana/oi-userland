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
# Copyright (c) 2014 Alexander Pyhalov
# Copyright (c) 2014 Ken Mays
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		metacity
COMPONENT_VERSION=	2.30.3
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	GNOME window manager
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:08f887018fa5e447cf184d03bae3fe2c05fdb7583bed6768e3b4d66392fc18dd
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.30/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cp $(COMPONENT_DIR)/files/*.png $(@D)/src &&\
					cd $(@D)  &&\
					libtoolize --copy --force &&\
					intltoolize --force --copy &&\
					aclocal -I . &&\
					autoconf &&\
					autoheader &&\
					automake -c -f -a )

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -rp $(SOURCE_DIR)/* $(@D) && \
                                        cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE) all )

CONFIGURE_SCRIPT = $(@D)/configure

CFLAGS += -Wno-deprecated-declarations
CFLAGS += -Icore -Iui
CFLAGS += -I/usr/X11/include -I/usr/include/freetype2 -DANSICPP -D__EXTENSIONS__
LDFLAGS +=  -L/usr/X11/lib -R/usr/X11/lib -lXrender
LDFLAGS += -lgthread-2.0

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
