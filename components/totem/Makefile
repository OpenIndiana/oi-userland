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
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= totem
COMPONENT_VERSION= 2.30.2
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Totem Multimedia Player
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:c50da5479c57b2791c3c1bfc05f815d5ee06082fcd1bacc49f4d88c11ed02b6d
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.30/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

#CXXFLAGS+= -DMOZ_DEFAULT_TOOLKIT=\"cairo-gtk2\"
#CXXFLAGS+= -std=gnu++0x

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D) && cd $(@D) && autoconf)

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --localstatedir=/var/lib
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib
CONFIGURE_OPTIONS+= --enable-browser-plugins
CONFIGURE_ENV    += PYTHON=$(PYTHON)
CONFIGURE_ENV    += MOZILLA_PLUGINDIR=/usr/lib/firefox/browser/plugins
COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32)

install: $(INSTALL_32)
