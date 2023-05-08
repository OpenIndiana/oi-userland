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

BUILD_BITS= 32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gparted
COMPONENT_VERSION= 0.4.5
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= GNOME Partition Editor
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:a0a102ee51c1d70fa1c786c77a613111179ce81efccb637bd04aef525199b93f
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/gparted/files/gparted/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://gparted.org/
COMPONENT_FMRI = desktop/administration/gparted
COMPONENT_CLASSIFICATION = System/Administration and Configuration
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

PATH = $(PATH.gnu)

include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -std=c++11

# Build dependencies
REQUIRED_PACKAGES += text/rarian
REQUIRED_PACKAGES += developer/gnome/gnome-doc-utils

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/atkmm
REQUIRED_PACKAGES += library/desktop/c++/gtkmm
REQUIRED_PACKAGES += library/desktop/c++/pangomm
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/storage/parted
