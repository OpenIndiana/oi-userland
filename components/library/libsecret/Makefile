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
BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
USE_COMMON_TEST_MASTER= no
SINGLE_PYTHON_VERSION= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libsecret
COMPONENT_MAJOR_VERSION= 0.20
COMPONENT_VERSION=		$(COMPONENT_MAJOR_VERSION).5
COMPONENT_SUMMARY=      GObject based library for accessing the Secret Service API
COMPONENT_PROJECT_URL=  https://www.gnome.org
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:3fb3ce340fcd7db54d87c893e69bfc2b1f6e4d4b279065ffe66dac9f0fd12b4d
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Security
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CONFIGURE_OPTIONS.32 += -Dintrospection=false
CONFIGURE_OPTIONS.32 += -Dvapi=false
CONFIGURE_OPTIONS.32 += -Dgtk_doc=false

COMPONENT_TEST_TRANSFORMS = \
	' -n ' \
	' -e "s/[0-9][0-9]*\.[0-9][0-9]*s//" ' \
	' -e "/OK/p" ' \
	' -e "/FAIL/p" ' \
	' -e "/Ok/p" ' \
	' -e "/Fail/p" ' \
	' -e "/Skipped/p" ' \
	' -e "/Timeout/p" ' \
	' -e "/Pass/p" '

# Manually added dependencies
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
