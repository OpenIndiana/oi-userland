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

COMPONENT_NAME= libpqxx

COMPONENT_VERSION= 4.0.1
COMPONENT_SUMMARY= C++ binding library for PostgreSQL
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:097ceda2797761ce517faa5bee186c883df1c407cb2aada613a16773afeedc38
COMPONENT_ARCHIVE_URL= \
  http://pqxx.org/download/software/libpqxx/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://pqxx.org/development/libpqxx/

# Don't depend on host default pg_config
PATH=$(PG_BINDIR.$(BITS)):/usr/sbin:/usr/bin

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; \
	   automake;\
	   autoconf )

PKG_CONFIG_PATH.32   = /usr/g++/lib/pkgconfig:/usr/lib/pkgconfig
PKG_CONFIG_PATH.64   = /usr/g++/lib/$(MACH64)/pkgconfig:/usr/lib/$(MACH64)/pkgconfig

CONFIGURE_PREFIX= /usr/g++
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

COMPONENT_POST_INSTALL_ACTION= ( mkdir -p $(PROTO_DIR)/usr/g++/share/doc/libpqxx-4.0 && \
	 cp -a $(SOURCE_DIR)/doc/html/* $(PROTO_DIR)/usr/g++/share/doc/libpqxx-4.0 )  

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
