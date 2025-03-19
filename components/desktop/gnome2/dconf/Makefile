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
BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         dconf
COMPONENT_MJR_VERSION=  0.40
COMPONENT_VERSION=      $(COMPONENT_MJR_VERSION).0
COMPONENT_REVISION=		2
COMPONENT_SUMMARY=      GNOME Configuration Framework
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Projects/dconf
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:cf7f22a4c9200421d8d3325c5c1b8b93a36843650c9f95d6451e20f0bcb24533
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         gnome/config/dconf
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CC_PIC_MODE = $(CC_PIC_DISABLE)
LD_Z_PIE_MODE = $(LD_Z_PIE_DISABLE)

COMPONENT_INSTALL_ENV += PATH="$(PATH.gnu)"
COMPONENT_BUILD_ENV += PATH="$(PATH.gnu)"
CONFIGURE_OPTIONS += -Dgtk_doc=true

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/[0-9]*\.[0-9]*s//" ' \
	'-e "/FAIL/p" ' \
	'-e "/OK/p" '


# Manually added build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/vala

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/glib2/32
REQUIRED_PACKAGES += system/library
