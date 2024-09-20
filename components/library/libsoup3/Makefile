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
# Copyright 2023 Andreas Wacknitz
#

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libsoup3
COMPONENT_VERSION= 3.6.0
COMPONENT_SUMMARY= Libsoup is an HTTP client/server library for GNOME
COMPONENT_SRC= libsoup-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:62959f791e8e8442f8c13cedac8c4919d78f9120d5bb5301be67a5e53318b4a3
COMPONENT_ARCHIVE_URL= https://download.gnome.org/sources/libsoup/3.6/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://wiki.gnome.org/Projects/libsoup
COMPONENT_FMRI= library/libsoup3
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE= COPYING

#TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= "$(PATH.gnu):/usr/apache2/2.4/bin"

COMPONENT_PRE_CONFIGURE_ACTION = ( \
        $(CP) $(COMPONENT_DIR)/files/krb5-config $(BUILD_DIR) && \
        chmod u+x $(BUILD_DIR)/krb5-config )

COMPONENT_CONFIGURE_ENV += PATH="$(PATH)"
COMPONENT_BUILD_ENV += PATH="$(PATH)"
COMPONENT_TEST_ENV += PATH="$(PATH)"

CONFIGURE_OPTIONS += -Dsysprof=disabled
CONFIGURE_OPTIONS += -Dkrb5_config=$(BUILD_DIR)/krb5-config

unexport SHELLOPTS
#COMPONENT_TEST_TRANSFORMS += ' -e "s/[0-9]*\.[0-9]*s//" '

# Manually added dependencies
PYTHON_REQUIRED_PACKAGES += library/python/gi-docgen
TEST_REQUIRED_PACKAGES += web/server/apache-24
REQUIRED_PACKAGES += library/glib-networking

# Auto-generated dependencies
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/brotli
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libpsl
REQUIRED_PACKAGES += library/nghttp2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
