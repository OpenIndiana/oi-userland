#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= webkitgtk
COMPONENT_VERSION= 2.10.4
COMPONENT_SUMMARY= Web content engine library for GTK+
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:dbf8260da5cac0c74de2d3cce1fe7c519da3cd816a2c769cb6c6d56addd2f055
COMPONENT_ARCHIVE_URL= \
  http://webkitgtk.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include ../../make-rules/prep.mk
include ../../make-rules/cmake.mk
include ../../make-rules/ips.mk

LDFLAGS+=-lm -lsocket

CMAKE_OPTIONS += -DPORT=GTK
CMAKE_OPTIONS += -DENABLE_INTROSPECTION=off
CMAKE_OPTIONS += -DENABLE_CREDENTIAL_STORAGE=off
CMAKE_OPTIONS += -DENABLE_GEOLOCATION=off
CMAKE_OPTIONS += -DENABLE_WEB_AUDIO=off
CMAKE_OPTIONS += -DENABLE_VIDEO=off
CMAKE_OPTIONS += -DUSE_LIBHYPHEN=off
CMAKE_OPTIONS += -DUSE_LIBNOTIFY=off
CMAKE_OPTIONS += -DUSE_SYSTEM_MALLOC=on
CMAKE_OPTIONS += -DLIBEXECDIR=/usr/lib
CMAKE_OPTIONS += -DCMAKE_INSTALL_LIBEXECDIR:PATH=lib

build: $(BUILD_32)

install: $(INSTALL_32)
