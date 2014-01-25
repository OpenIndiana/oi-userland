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
# Copyright (c) 2013 Ken Mays
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=                brasero
COMPONENT_VERSION=        2.30.3
COMPONENT_PROJECT_URL=        https://projects.gnome.org/brasero/
COMPONENT_SUMMARY=        Gnome CD/DVD burner
COMPONENT_SRC=                $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=        \
    sha256:343b393a23a1215514ab096fe512160eef6c0ae24ae705d5d952d663f6cebbd3
COMPONENT_ARCHIVE_URL=        http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.30/$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

COMPONENT_PREP_ACTION = \
        (cd $(@D);  libtoolize --copy --force ; \
                aclocal -I . ; \
                autoheader ; \
                automake --add-missing --copy ; \
                autoconf)
                                        
CONFIGURE_OPTIONS+=        --sysconfdir=/etc
CONFIGURE_OPTIONS+=        --libexecdir=/usr/lib
CONFIGURE_OPTIONS+=        --localstatedir=/var
CONFIGURE_OPTIONS+=        --enable-shared
CONFIGURE_OPTIONS+=        --disable-static
CONFIGURE_OPTIONS+=        --disable-scrollkeeper
CONFIGURE_OPTIONS+=        --enable-search
CONFIGURE_OPTIONS+=        --enable-playlist
CONFIGURE_OPTIONS+=        --enable-nautilus
CONFIGURE_OPTIONS+=        --enable-introspection
CONFIGURE_OPTIONS+=        --enable-libburnia
CONFIGURE_OPTIONS+=        --disable-gtk-doc
CONFIGURE_OPTIONS+=        --disable-inotify

COMPONENT_INSTALL_ENV+=        GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:                $(BUILD_32)

install:        $(INSTALL_32)

test:                $(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
