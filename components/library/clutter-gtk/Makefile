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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2023 Friedrich Kink.  All rights reserved.
#

BUILD_STYLE=configure
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         clutter-gtk
COMPONENT_VERSION=      1.8.4
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      GTK+ integration library for clutter
COMPONENT_FMRI=         library/desktop/clutter/clutter-gtk
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:521493ec038973c77edcb8bc5eac23eed41645117894aaee7300b2487cb42b06
COMPONENT_ARCHIVE_URL=  \
	https://download.gnome.org/sources/$(COMPONENT_NAME)/1.8/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  http://www.clutter-project.org/

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH = /usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
					aclocal -I./build/autotools && \
					autoheader && \
					libtoolize --automake --copy --force && \
					automake -a -f -c &&\
					autoconf )

LDFLAGS += -lm -lgthread-2.0

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)

# Tell g-ir-scanner about compiler
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

ifeq ($(strip $(MACH)),sparc)
REQUIRED_PACKAGES += system/library/math
endif

# Build dependencies
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/cogl
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
