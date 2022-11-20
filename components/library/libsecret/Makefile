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
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_COMMON_TEST_MASTER= no
SINGLE_PYTHON_VERSION= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libsecret
COMPONENT_MAJOR_VERSION= 0.20
COMPONENT_VERSION=		$(COMPONENT_MAJOR_VERSION).4
COMPONENT_SUMMARY=      GObject based library for accessing the Secret Service API
COMPONENT_PROJECT_URL=  https://www.gnome.org
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:325a4c54db320c406711bf2b55e5cb5b6c29823426aa82596a907595abb39d28
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Security
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

# If we use gcc-7 vala tests cannot be build because of a 32/64 bit ELFCLASS mismatch.
GCC_VERSION= 10

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS.32 += --disable-introspection
CONFIGURE_OPTIONS.64 += --enable-introspection
CONFIGURE_OPTIONS.32 += --disable-vala
CONFIGURE_OPTIONS.64 += --enable-vala

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_TEST_ENV += CC="$(CC)"
COMPONENT_TEST_ENV += CFLAGS="$(CFLAGS)"

# Manually added dependencies
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
