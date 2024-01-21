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

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         yelp
COMPONENT_VERSION=      42.2
COMPONENT_VERSION_MAJOR=$(word 1,$(subst ., ,$(HUMAN_VERSION)))
COMPONENT_SUMMARY=      The GNOME Help Browser
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:a2c5fd0787a9089c722cc66bd0f85cdf7088d870e7b6cc85799f8e5bff9eac4b
COMPONENT_ARCHIVE_URL=  \
	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION_MAJOR)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.gnome.org
COMPONENT_FMRI=         gnome/help-viewer/yelp
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Documentation
COMPONENT_LICENSE=      GPL-2.0-only
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

# configure expects GNU make in PATH
PATH = $(PATH.gnu)

# We do not have appstream-glib so we cannot call autoreconf
COMPONENT_PREP_ACTION = cd $(@D) && automake

# illumos ld does not understand --no-as-needed, but configure is unable to
# detect that properly
CONFIGURE_ENV += ax_cv_check_cflags__Wl___no_as_needed=no

# Build dependencies
REQUIRED_PACKAGES += library/gnome/yelp-tools
REQUIRED_PACKAGES += library/gnome/yelp-xsl

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/webkitgtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libhandy
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/man
REQUIRED_PACKAGES += text/groff/groff-core
