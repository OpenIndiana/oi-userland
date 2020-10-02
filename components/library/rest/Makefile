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
# Copyright 2017 Alexander Pyhalov
#

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= rest
COMPONENT_VERSION= 0.8.1
COMPONENT_SUMMARY= A library designed to make it easier to access web services that claim to be 'RESTful'
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:0513aad38e5d3cedd4ae3c551634e3be1b9baaa79775e53b2dba9456f15b01c9
COMPONENT_ARCHIVE_URL= \
	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.8/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://wiki.gnome.org/Projects/Librest
COMPONENT_FMRI = library/desktop/librest
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --with-ca-certificates=/etc/certs/ca-certificates.crt
CONFIGURE_OPTIONS.64 += --enable-introspection

# gobject introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# for tests to pass
unexport SHELLOPTS
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL:/p" ' \
	'-e "/SKIP:/p" ' \
	'-e "/PASS:/p" ' \
	'-e "/FAIL:/p" ' \
	'-e "/ERROR:/p" '

# Manually added dependency
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
