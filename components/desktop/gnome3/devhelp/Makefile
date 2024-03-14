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

BUILD_STYLE= meson
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= devhelp
COMPONENT_MJR_VERSION= 43
COMPONENT_MNR_VERSION= 0
COMPONENT_VERSION= $(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SUMMARY= API documentation browser for GNOME
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:63ceeefd05392e02044881ef1ecd724293553da5735b7efc082b2d13fe85dd04
COMPONENT_ARCHIVE_URL= https://download.gnome.org/sources/devhelp/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://wiki.gnome.org/Apps/Devhelp
COMPONENT_FMRI= developer/gnome/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Development/GNOME and GTK+
COMPONENT_LICENSE= GPLv3+,CC BY-SA 4.0

include $(WS_MAKE_RULES)/common.mk

# g-ir-scanner
CC_PIC_MODE= $(CC_PIC_DISABLE)
LD_Z_PIE_MODE= $(LD_Z_PIE_DISABLE)

# need to use gnu-gettext
CONFIGURE_ENV += PATH=$(PATH.gnu)
COMPONENT_INSTALL_ENV += PATH=$(PATH.gnu)
COMPONENT_BUILD_ENV += PATH=$(PATH.gnu)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/webkitgtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
