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
# Copyright 2016 Till Wegmueller
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libnotify
COMPONENT_VERSION=	0.8.7
COMPONENT_SUMMARY=      Library for desktop notifications
COMPONENT_ARCHIVE_HASH=	sha256:4be15202ec4184fce1ac15997ece5530d2be32fe9573875aeb10e3b573858748
COMPONENT_FMRI=         library/libnotify
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# we miss docbook-xsl-ns
CONFIGURE_OPTIONS += -Dman=false

# Testing needs an X server
# The tests work best without a running non-system dbus.
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :1 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:1
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Manually added build dependencies
REQUIRED_PACKAGES.python += library/python/gi-docgen
# python-dbusmock is needed to build tests
REQUIRED_PACKAGES.python += library/python/python-dbusmock

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
