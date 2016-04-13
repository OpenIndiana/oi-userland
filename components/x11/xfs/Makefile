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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= xfs
COMPONENT_VERSION= 1.1.4
COMPONENT_SUMMARY= xfs - X Font Server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:a40b75e674c091464f85739292b6bf24e2d153f4a2ac456d3ea6b8a64e269ffa
COMPONENT_ARCHIVE_URL= \
  http://ftp.x.org/pub/individual/app/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.x.org/wiki/
COMPONENT_FMRI= x11/xfs
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION= System/X11

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --sysconfdir=/usr/lib
CONFIGURE_OPTIONS += --enable-syslog
CONFIGURE_OPTIONS += --enable-inetd
CONFIGURE_OPTIONS += --disable-devel-docs
CONFIGURE_OPTIONS += --with-default-font-path='catalogue:/etc/X11/fontpath.d'
CONFIGURE_OPTIONS += --with-default-config-file='/etc/X11/fs/config,/usr/lib/X11/fs/config,/etc/openwin/fs/fontserver.cfg,/usr/openwin/lib/X11/fontserver.cfg'

CPPFLAGS += -DNO_ALLOCA

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)
