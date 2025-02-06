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
HUMAN_VERSION= 2.80.1
COMPONENT_SUMMARY= Network-related giomodules for glib
COMPONENT_ARCHIVE_HASH= sha256:b80e2874157cd55071f1b6710fa0b911d5ac5de106a9ee2a4c9c7bee61782f8e
COMPONENT_FMRI = library/glib-networking
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= LGPL-2.1-only WITH cryptsetup-OpenSSL-exception

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		printf -- '--- COPYING ---------------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING ; \
		printf '\n\n--- LICENSE_EXCEPTION -----------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/LICENSE_EXCEPTION \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += system/library
