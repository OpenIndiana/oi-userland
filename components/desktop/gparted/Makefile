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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gparted
COMPONENT_VERSION= 0.4.5
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= GNOME Partition Editor
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:a0a102ee51c1d70fa1c786c77a613111179ce81efccb637bd04aef525199b93f
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/gparted/files/gparted/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gparted.org/
COMPONENT_FMRI = desktop/administration/gparted
COMPONENT_CLASSIFICATION = System/Administration and Configuration
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = COPYING

PATH=$(PATH.gnu)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CXXFLAGS+= -std=c++11

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += text/rarian

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/atkmm
REQUIRED_PACKAGES += library/desktop/c++/gtkmm
REQUIRED_PACKAGES += library/desktop/c++/pangomm
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-6-runtime
REQUIRED_PACKAGES += system/storage/parted
