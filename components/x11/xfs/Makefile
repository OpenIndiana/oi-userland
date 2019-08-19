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

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    xfs
COMPONENT_VERSION= 1.2.0
COMPONENT_SUMMARY= xfs - X Font Server
COMPONENT_FMRI=    x11/xfs
COMPONENT_ARCHIVE_HASH= \
  sha256:db2212115783498f8eeaaee1349461d6c4e9d2005e142bacd3a984fe57269860
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=/usr/lib
CONFIGURE_OPTIONS += --enable-syslog
CONFIGURE_OPTIONS += --enable-inetd
CONFIGURE_OPTIONS += --disable-devel-docs
CONFIGURE_OPTIONS += --with-default-font-path='catalogue:/etc/X11/fontpath.d'
CONFIGURE_OPTIONS += --with-default-config-file='/etc/X11/fs/config,/usr/lib/X11/fs/config,/etc/openwin/fs/fontserver.cfg,/usr/openwin/lib/X11/fontserver.cfg'

CPPFLAGS += -DNO_ALLOCA

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Build dependencies
REQUIRED_PACKAGES += x11/library/xtrans

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxfont2
