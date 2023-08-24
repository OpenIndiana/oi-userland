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
# Copyright 2023 Niklas Poslovski
#

BUILD_STYLE = meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libsoup3
COMPONENT_VERSION= 3.4.2
COMPONENT_SUMMARY= Libsoup is an HTTP client/server library for GNOME
COMPONENT_SRC= libsoup-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:78c8fa37cb152d40ec8c4a148d6155e2f6947f3f1602a7cda3a31ad40f5ee2f3
COMPONENT_ARCHIVE_URL= https://download.gnome.org/sources/libsoup/3.4/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://wiki.gnome.org/Projects/libsoup
COMPONENT_FMRI= library/libsoup3
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION = ( \
        $(CP) $(COMPONENT_DIR)/files/krb5-config $(BUILD_DIR) && \
        chmod u+x $(BUILD_DIR)/krb5-config )

CONFIGURE_OPTIONS += -Dsysprof=disabled
CONFIGURE_OPTIONS += -Dkrb5_config=$(BUILD_DIR)/krb5-config

# Build dependencies
REQUIRED_PACKAGES += library/glib-networking
PYTHON_REQUIRED_PACKAGES += library/python/gi-docgen

# Auto-generated dependencies
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libpsl
REQUIRED_PACKAGES += library/nghttp2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
