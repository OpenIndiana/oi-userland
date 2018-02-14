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

COMPONENT_NAME= lightdm-gtk-greeter
COMPONENT_VERSION= 2.0.2
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= GTK greeter for LDM
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:8ee6d93d1d6837b3590f64ac4d5bac5db888a8861dff1cb2ef10f7816ad36690
COMPONENT_ARCHIVE_URL= \
  https://launchpad.net/lightdm-gtk-greeter/2.0/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://launchpad.net/lightdm-gtk-greeter/
COMPONENT_FMRI = system/display-manager/lightdm/gtk-greeter
COMPONENT_CLASSIFICATION=       Desktop (GNOME)/Sessions
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = (cd $(@D) && autoreconf -fi)

CONFIGURE_SBINDIR.64 = $(CONFIGURE_SBINDIR.32)

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --disable-indicator-services-command
CONFIGURE_OPTIONS += --disable-at-spi-command

CONFIGURE_ENV += XGETTEXT=/usr/gnu/bin/xgettext

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

build: $(BUILD_64)

install: $(INSTALL_64)

REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/display-manager/lightdm
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
