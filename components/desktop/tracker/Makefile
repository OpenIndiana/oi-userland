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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= tracker

COMPONENT_VERSION= 0.10.37
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Desktop search tool
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:33d9fe0aa58e2249d1907365676a8fba5686e3df0f127b499e18bf2ee170659d
COMPONENT_ARCHIVE_URL= \
  http://download.gnome.org/sources/$(COMPONENT_NAME)/0.10/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.tracker-project.org

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS	+= -D__EXTENSIONS__
CFLAGS	+= -DO_NOATIME=0
# illumos-gate provides libuuid, but not uuid.pc
LDFLAGS += -luuid

COMPONENT_PREP_ACTION= ( cd $(@D) && \
                libtoolize --force &&\
                aclocal -I . &&\
                autoheader &&\
                automake -a -c -f &&\
                autoconf )

COMPONENT_PRE_CONFIGURE_ACTION =        ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS+= --disable-warnings
CONFIGURE_OPTIONS+= --enable-external-sqlite
CONFIGURE_OPTIONS+= --disable-evolution-push-module

CONFIGURE_ENV    += PERL=$(PERL)

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

build: $(BUILD_32)

install: $(INSTALL_32)
