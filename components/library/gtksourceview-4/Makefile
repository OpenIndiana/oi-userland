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
# Copyright 2017 Geoffrey Weiss
# Copyright (c) 2021 Tim Mooney.  All rights reserved
#

BUILD_STYLE= meson
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gtksourceview
COMPONENT_MAJOR_MINOR=	4.8
COMPONENT_VERSION=	$(COMPONENT_MAJOR_MINOR).4
COMPONENT_SUMMARY=	Multiline text editing library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MAJOR_MINOR)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:7ec9d18fb283d1f84a3a3eff3b7a72b09a10c9c006597b3fbabbb5958420a87d
COMPONENT_FMRI=		library/desktop/gtksourceview4
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

CONFIGURE_ENV += INTLTOOL_PERL="$(PERL)"

CONFIGURE_OPTIONS += --libexecdir=/usr/lib
CONFIGURE_OPTIONS += --localstatedir=/var/lib
CONFIGURE_OPTIONS += --sysconfdir=/etc
# this project uses 'gir' for the introspection flag
CONFIGURE_OPTIONS.32 += -Dgir=false
CONFIGURE_OPTIONS.64 += -Dgir=true
# fairly optional, disable if it causes problems for later builds
CONFIGURE_OPTIONS.64 += -Dglade_catalog=true

# if you do run the tests, use these transforms  
# (first) delete the timing information from any line
# delete the "exit status N", it can cause issues too
# print lines that start with " N/NNN"
# print everything between "^Ok:" and "^Timeout:"
# delete the ninja log-related stuff at the end
unexport SHELLOPTS

COMPONENT_TEST_TRANSFORMS += \
    '-n ' \
    '-e "/^Ok:/p" ' \
    '-e "/^Expected Fail:/p" ' \
    '-e "/^Fail:/p" ' \
	'-e "/^Skipped:/p" ' \
	'-e "/^Timeout:/p" ' \
    '-e "/^Unexpected Pass:/p" ' \
    '-e "/^Full log written.*/,/^ninja: build stopped.*/d" '


# build requirement for the 64-bit build
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += developer/vala
# required for the glade_catalog option
REQUIRED_PACKAGES += developer/ui-designer/glade

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
