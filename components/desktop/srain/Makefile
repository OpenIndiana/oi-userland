#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2024 Geoff Weiss
#

BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         srain
COMPONENT_VERSION=      1.8.0
COMPONENT_SUMMARY=      Modern IRC client written in GTK.
COMPONENT_PROJECT_URL=  https://srain.silverrainz.me/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:0c9830c79a3d5656bfe6aaf926f091b09b57eaacbfdc98270c40274fdbd680c2
COMPONENT_ARCHIVE_URL=  https://github.com/SrainApp/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         desktop/irc/srain
COMPONENT_CLASSIFICATION=Applications/Internet
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# OI's ayatana-appindicator is too old
CONFIGURE_OPTIONS += -Dapp_indicator=false

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libconfig
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libsoup3
REQUIRED_PACKAGES += system/library
