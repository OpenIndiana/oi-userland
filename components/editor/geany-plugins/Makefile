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
# Copyright 2016-2017 Predrag Zečević.  All rights reserved.
# Copyright 2022 Nona Hansel
# Copyright 2023 Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         geany-plugins
COMPONENT_VERSION=      2.0
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      Plugins for Geany editor
COMPONENT_DESCRIPTION=	Geany-Plugins is a collection of different plugins for Geany, a lightweight IDE.
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:cd7d27f00aef4afe2040d7e5246a863234c340c8520ef698be9a15005ed8f57e
COMPONENT_PROJECT_URL=  https://plugins.geany.org
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         editor/geany/plugins
COMPONENT_CLASSIFICATION= System/Text Tools
COMPONENT_LICENSE=      GPLv2

COMPONENT_PREP_ACTION += ( cd $(@D) && rm ltmain.sh; autoreconf -fi )

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

CFLAGS += $(XPG6MODE)
CFLAGS += -D_FILE_OFFSET_BITS=64
# gcc 14 complains about incompatible pointer types
CFLAGS += -Wno-error=incompatible-pointer-types

CONFIGURE_ENV += CHECK_CFLAGS="-I/usr/include/check"
CONFIGURE_ENV += PYTHON=$(PYTHON.3.9.64)

# requires libutil
CONFIGURE_OPTIONS += --disable-debugger
CONFIGURE_OPTIONS += --disable-scope

# no lipsum (www.lipsum.com) in OI yet
CONFIGURE_OPTIONS += --disable-lipsum

# Enable to avoid relying on the environment
CONFIGURE_OPTIONS += --enable-gtkspell

# Manually added build dependencies
REQUIRED_PACKAGES += gnome/config/gconf

# Auto-generated dependencies
REQUIRED_PACKAGES += editor/geany
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/gtkspell3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libgit2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/security/gpgme
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += system/library
