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
# Copyright 2015 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

BUILD_BITS=	64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         dbus-glib
COMPONENT_VERSION=      0.116
COMPONENT_SUMMARY=      D-Bus GLib bindings
COMPONENT_PROJECT_URL=  https://dbus.freedesktop.org/doc/dbus-glib/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e3f3d4487e2883800770ed5899ed111bdc4ba7056af34a255c4c46ad8a2486f3
COMPONENT_ARCHIVE_URL=  https://dbus.freedesktop.org/releases/dbus-glib/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         system/library/libdbus-glib
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      GPLv2,AFLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-tests
CONFIGURE_OPTIONS += --enable-bash-completion

COMPONENT_TEST_ARGS += -k

# Auto-generated dependencies
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/expat/32
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/glib2/32
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus/32
