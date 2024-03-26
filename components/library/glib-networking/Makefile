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

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= glib-networking
COMPONENT_MAJOR_VERSION= 2.76
COMPONENT_VERSION= $(COMPONENT_MAJOR_VERSION).1
COMPONENT_SUMMARY= Network-related giomodules for glib
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:5c698a9994dde51efdfb1026a56698a221d6250e89dc50ebcddda7b81480a42b
COMPONENT_ARCHIVE_URL= https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://www.gnome.org
COMPONENT_FMRI = library/glib-networking
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= LGPLv2.1+OpenSSL exception

include $(WS_MAKE_RULES)/common.mk

# Assumes GNU xgettext in PATH
CONFIGURE_ENV += PATH=$(PATH.gnu)
COMPONENT_INSTALL_ENV += PATH=$(PATH.gnu)
COMPONENT_BUILD_ENV += PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += system/library
