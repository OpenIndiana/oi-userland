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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= rest
COMPONENT_VERSION= 0.8.0
COMPONENT_SUMMARY= A library designed to make it easier to access web services that claim to be 'RESTful'
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:e7b89b200c1417073aef739e8a27ff2ab578056c27796ec74f5886a5e0dff647
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.8/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://wiki.gnome.org/Projects/Librest
COMPONENT_FMRI = library/desktop/librest
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS += --with-ca-certificates=/etc/certs/ca-certificates.crt
CONFIGURE_OPTIONS += --enable-introspection

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

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
