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

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= glib-networking
COMPONENT_MAJOR_VERSION= 2.42
COMPONENT_VERSION= $(COMPONENT_MAJOR_VERSION).0
COMPONENT_REVISION= 5
COMPONENT_SUMMARY= Network-related giomodules for glib
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:304dd9e4c0ced69094300e0b9e66cd2eaae7161b9fc3186536d11458677d820d
COMPONENT_ARCHIVE_URL= \
  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.gnome.org
COMPONENT_FMRI = library/glib-networking
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --with-ca-certificates=/etc/certs/ca-certificates.crt
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)

CONFIGURE_ENV += XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV += MSGFMT=/usr/gnu/bin/msgfmt

COMPONENT_INSTALL_ENV+= GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# Tell g-ir-scanner about compiler
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

REQUIRED_PACKAGES += library/desktop/p11-kit
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += system/library
# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/p11-kit
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += system/library
