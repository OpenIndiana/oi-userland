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

COMPONENT_NAME= gvfs
COMPONENT_VERSION= 1.26.0
COMPONENT_REVISION= 4
COMPONENT_SUMMARY= GNOME virtual file system framework
COMPONENT_FMRI= library/gnome/gvfs
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:6d43e8b33a5c1588525875f9d3979b515f648da1d567d0ce3d337a18f5ff8c32
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/1.26/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = /usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        (cd $(@D) && \
					autoreconf -if)

CFLAGS += -D_XPG4_2
CFLAGS += -D__EXTENSIONS__
CFLAGS.32 += -I/usr/include/libsmbclient
LDFLAGS += -lxml2
LDFLAGS.32 = -L/usr/lib/libsmbclient -R/usr/lib/libsmbclient
LDFLAGS += $(LDFLAGS.$(BITS))

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-fuse
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-avahi
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --enable-archive
CONFIGURE_OPTIONS += --enable-bash-completion
CONFIGURE_OPTIONS += --enable-documentation
CONFIGURE_OPTIONS += --enable-goa
CONFIGURE_OPTIONS += --disable-gphoto2
CONFIGURE_OPTIONS += --disable-bluray
CONFIGURE_OPTIONS += --enable-gtk
CONFIGURE_OPTIONS += --enable-http
CONFIGURE_OPTIONS += --enable-keyring
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic

CONFIGURE_OPTIONS.32 += --with-samba-includes=/usr/include/libsmbclient
CONFIGURE_OPTIONS.32 += --with-samba-libs=/usr/lib/libsmbclient

CONFIGURE_ENV+= PERL=$(PERL)

$(INSTALL_32):	$(INSTALL_64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/samba/libsmbclient
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/network/avahi
