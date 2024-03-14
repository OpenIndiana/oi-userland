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
# Copyright 2016 Alexander Pyhalov
#

BUILD_STYLE= meson
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         dconf-editor
COMPONENT_MJR_VERSION=  45
COMPONENT_VERSION=      $(COMPONENT_MJR_VERSION).0.1
COMPONENT_SUMMARY=      GNOME Configuration Editor
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/dconf
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:1180297678eedae6217cc514a2638c187d2f1d1ef2720cb9079b740c429941dd
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         gnome/config/dconf/dconf-editor
COMPONENT_CLASSIFICATION=Applications/Configuration and Preferences
COMPONENT_LICENSE=      LGPLv3
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# GNU xgettext is needed.
CONFIGURE_ENV += PATH=$(PATH.gnu)
COMPONENT_BUILD_ENV += PATH=$(PATH.gnu)
COMPONENT_INSTALL_ENV += PATH=$(PATH.gnu)

# Manually added build dependencies
REQUIRED_PACKAGES += developer/build/pkg-config
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/libxml2

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/config/dconf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libhandy
REQUIRED_PACKAGES += system/library
