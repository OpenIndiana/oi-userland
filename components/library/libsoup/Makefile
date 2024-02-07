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

BUILD_BITS= 64
BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libsoup
COMPONENT_MJR_VERSION= 2.74
COMPONENT_REVISION= 1
COMPONENT_VERSION= $(COMPONENT_MJR_VERSION).3
COMPONENT_SUMMARY= Libsoup is an HTTP client/server library for GNOME
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:e4b77c41cfc4c8c5a035fcdc320c7bc6cfb75ef7c5a034153df1413fa1d92f13
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://www.gnome.org
COMPONENT_FMRI = library/libsoup
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/common.mk

# Make sure apachectl and https will be found
PATH= $(PATH.gnu):/usr/apache2/2.4/bin

CFLAGS += $(XPG6MODE)
LDFLAGS += -lz

COMPONENT_PRE_CONFIGURE_ACTION = ( \
	$(CP) $(COMPONENT_DIR)/files/krb5-config $(BUILD_DIR) && \
	chmod u+x $(BUILD_DIR)/krb5-config )

CONFIGURE_OPTIONS += -Dkrb5_config=$(BUILD_DIR)/krb5-config
CONFIGURE_OPTIONS += -Dsysprof=disabled
CONFIGURE_OPTIONS += -Dgtk_doc=true

# Manually added build dependencies
REQUIRED_PACKAGES += library/glib-networking
TEST_REQUIRED_PACKAGES += service/network/samba
TEST_REQUIRED_PACKAGES += web/server/apache-24

# Auto-generated dependencies
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libpsl
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
