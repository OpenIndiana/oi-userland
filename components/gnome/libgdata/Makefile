#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER=gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgdata
COMPONENT_VERSION=	0.17.3
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/libgdata
COMPONENT_ARCHIVE_HASH=	\
    sha256:ff280b031c50a99ed735c3fa18fbea9ae3e4cc5e3d7dd58ebae09994b01b513b
COMPONENT_BUGDB=        gnome/libraries

TPNO=			25082

# Needs gobject-introspection, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# Documentation XML is malformed; skip building.
CONFIGURE_OPTIONS += --disable-gtk-doc
CONFIGURE_OPTIONS += --disable-static
# Required for other components.
CONFIGURE_OPTIONS += --enable-gnome
CONFIGURE_OPTIONS += --enable-goa
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
# Required for other components.
CONFIGURE_OPTIONS += --enable-vala
CONFIGURE_OPTIONS += --with-pic

CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"

# Delete once builds servers have goa installed
GOA_BASE = $(WS_COMPONENTS)/gnome/gnome-online-accounts/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(GOA_BASE)/usr/lib/$(MACH64)/pkgconfig

LD_OPTIONS += -L $(GOA_BASE)$(USRLIB.$(BITS))

CONFIGURE_ENV += GNOME_CFLAGS="-D_REENTRANT -I$(GOA_BASE)/usr/include/goa-1.0 -I$(GOA_BASE)/usr/lib/$(MACH64)/goa-1.0/include -I/usr/include/gcr-3 -I/usr/include/gck-1 -I/usr/include/p11-kit-1 -I/usr/include/libxml2 -I/usr/include/glib-2.0 -I/usr/lib/$(MACH64)/glib-2.0/include"

COMPONENT_BUILD_ENV  += \
	XDG_DATA_DIRS="$(GOA_BASE)/usr/share/:/usr/share/"

COMPONENT_BUILD_ENV += LD_LIBRARY_PATH_64="$(GOA_BASE)$(USRLIB.$(BITS)):$(BUILD_DIR_64)/gdata/.libs"

# The dependency isn't installed, so add it manually since pkgdepend
# can't resolve them yet: 15708323
DEPENDED += $(WS_TOP)/components/gnome/gnome-online-accounts/build/manifest-$(MACH)-gnome-online-accounts.depend

# Temporary until dependencies are all on build machines
REQUIRED_PACKAGES += $(shell $(GSED) -n 's/REQUIRED_PACKAGES +=//p' ../gnome-online-accounts/Makefile)
#end Delete

# for the tests
unexport SHELLOPTS
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += library/gnome/gnome-online-accounts
REQUIRED_PACKAGES += library/json-glib
REQUIRED_PACKAGES += library/liboauth
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/uhttpmock
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
