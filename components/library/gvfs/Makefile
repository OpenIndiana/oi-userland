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

COMPONENT_NAME=         gvfs
COMPONENT_VERSION=      1.26.3
COMPONENT_SUMMARY=      GVfs is a userspace virtual filesystem implementation for GIO (GLib)
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/gvfs
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:a70f75fa60d66f3f478c0c8aec43d0e43455a8cc75a4dfa8029e51c816401b4a
COMPONENT_ARCHIVE_URL= 	https://download.gnome.org/sources/$(COMPONENT_NAME)/1.26/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/gnome/gvfs
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION= ( cd $(@D) && autoreconf -if )

CFLAGS += -Wno-deprecated-declarations -Wno-incompatible-pointer-types
CPPFLAGS += -D_XPG4_2 -D__EXTENSIONS__
LDFLAGS += -lxml2 -L/usr/lib/libsmbclient -R/usr/lib/libsmbclient

CONFIGURE_OPTIONS += --disable-fuse
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-avahi
CONFIGURE_OPTIONS += --enable-archive
CONFIGURE_OPTIONS += --enable-bash-completion
CONFIGURE_OPTIONS += --enable-documentation
CONFIGURE_OPTIONS += --enable-goa
# libbluray is in encumbered
CONFIGURE_OPTIONS += --disable-bluray
CONFIGURE_OPTIONS += --enable-gtk
CONFIGURE_OPTIONS += --enable-http
CONFIGURE_OPTIONS += --enable-keyring
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-samba-includes=/usr/include/libsmbclient
CONFIGURE_OPTIONS += --disable-libsystemd-login

CONFIGURE_ENV += PERL=$(PERL)
CONFIGURE_ENV += GLIB_COMPILE_SCHEMAS=/usr/bin/glib-compile-schemas

# Build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/gnome-mount
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/samba/libsmbclient
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/security/libgcrypt
REQUIRED_PACKAGES += system/network/avahi
