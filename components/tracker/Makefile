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

COMPONENT_NAME= tracker

COMPONENT_VERSION= 0.6.96
COMPONENT_SUMMARY= Desktop search tool
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:a3888daaa1c12358c373b3cf3edd00a5eed1056332152bb099947767d29d9b95
COMPONENT_ARCHIVE_URL= \
  http://download.gnome.org/sources/$(COMPONENT_NAME)/0.6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.tracker-project.org

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS	+= -D__EXTENSIONS__

COMPONENT_PREP_ACTION= ( cd $(@D) && \
                libtoolize --force &&\
                aclocal -I . &&\
                autoheader &&\
                automake -a -c -f &&\
                autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =        ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=/usr/bin
CONFIGURE_OPTIONS+= --disable-warnings
CONFIGURE_OPTIONS+= --enable-external-sqlite
CONFIGURE_OPTIONS+= --disable-evolution-push-module

CONFIGURE_ENV    += PERL=$(PERL)

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32)

install: $(INSTALL_32)
