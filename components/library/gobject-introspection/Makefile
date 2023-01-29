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
# Copyright 2016 Marcel Telka <marcel@telka.sk>
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2019 Michal Nowak
#

# IMPORTANT if the umask of the builder isn't set to 0022
# the resulting: /usr/lib/sparcv9/gobject-introspection/giscanner/__pycache__
# directory ends up with 700 - in the final installation and therefore
# can't be used by end-users !!!

BUILD_STYLE= meson
SINGLE_PYTHON_VERSION= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gobject-introspection

COMPONENT_VERSION_MAJOR= 1
COMPONENT_VERSION_MINOR= 72
COMPONENT_VERSION_MICRO= 0
COMPONENT_REVISION= 1
COMPONENT_VERSION_DL= $(COMPONENT_VERSION_MAJOR).$(COMPONENT_VERSION_MINOR)
COMPONENT_VERSION= $(COMPONENT_VERSION_DL).$(COMPONENT_VERSION_MICRO)
COMPONENT_SUMMARY= Introspection for GObject libraries
COMPONENT_PROJECT_URL= https://live.gnome.org/GObjectIntrospection
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:02fe8e590861d88f83060dd39cda5ccaa60b2da1d21d0f95499301b186beaabc
COMPONENT_ARCHIVE_URL= https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION_DL)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/desktop/gobject/gobject-introspection
COMPONENT_CLASSIFICATION= Development/GNOME and GTK+
COMPONENT_LICENSE= GPLv2, LGPLv2

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV += PYTHON=$(PYTHON)

# We have transfrom rules that re-add cpython-$(PYV) to manifest files. Thus, remove it here:
COMPONENT_POST_INSTALL_ACTION = (cd $(PROTOUSRLIBDIR)/$(MACH64)/$(COMPONENT_NAME)/giscanner; \
	$(MV) _giscanner.cpython-39.so _giscanner.so)

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/^Ok/p" ' \
	'-e "/^Expected/p" ' \
	'-e "/^Fail/p" ' \
	'-e "/^Unexpected/p" ' \
	'-e "/^Skipped/p" ' \
	'-e "/^Timeout/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/python/markdown
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
