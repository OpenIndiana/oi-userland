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

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gvfs
COMPONENT_VERSION=      1.26.0
COMPONENT_REVISION=     7
COMPONENT_SUMMARY=      GNOME virtual file system framework
COMPONENT_PROJECT_URL=  https://www.gnome.org
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:6d43e8b33a5c1588525875f9d3979b515f648da1d567d0ce3d337a18f5ff8c32
COMPONENT_ARCHIVE_URL= 	https://download.gnome.org/sources/$(COMPONENT_NAME)/1.26/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/gnome/gvfs
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      LGPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION= ( cd $(@D) && \
	autoreconf -if)

CPPFLAGS += -D_XPG4_2 -D__EXTENSIONS__
LDFLAGS += -lxml2 -L/usr/lib/libsmbclient/$(MACH64) -R/usr/lib/libsmbclient/$(MACH64)

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
CONFIGURE_OPTIONS += --with-samba-includes=/usr/include/libsmbclient

CONFIGURE_OPTIONS.32 += --without-samba
CONFIGURE_OPTIONS.64 += --with-samba
#CONFIGURE_OPTIONS.64 += --with-samba-libs=/usr/lib/libsmbclient/$(MACH64)
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

CONFIGURE_ENV+= PERL=$(PERL)
CONFIGURE_ENV+= GLIB_COMPILE_SCHEMAS=/usr/bin/glib-compile-schemas

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
