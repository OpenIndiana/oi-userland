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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		eog-plugins
COMPONENT_VERSION=	3.16.3
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/EyeOfGnome
COMPONENT_ARCHIVE_HASH= \
	sha256:2d2198ed026b1c28329ac3d353b3031c2024277d81d60f3c1e626f4701a73bd2
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/3.16/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/applications

TPNO=			26904

TEST_TARGET = $(NO_TESTS)

# Needs gobject-introspection, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

# Assumes GNU msgfmt is in PATH.
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

CONFIGURE_OPTIONS += --disable-static
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --with-cms
CONFIGURE_OPTIONS += --with-libexif
CONFIGURE_OPTIONS += --with-libjpeg
CONFIGURE_OPTIONS += --with-librsvg
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-x
CONFIGURE_OPTIONS += --with-xmp
# Enable postasa when an updated libgdata is delivered
# And also fix the *.p5m file with it
CONFIGURE_OPTIONS += --with-plugins="map,fit-to-width,exif-display,fullscreenbg,postr,pythonconsole,slideshowshuffle"

# Requires python 3.2 or newer
PYTHON_VERSION = 3.5

# Delete this when build servers are installed with an updated eog
EOG_BASE = $(WS_COMPONENTS)/gnome/eog/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(EOG_BASE)$(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS += -L$(EOG_BASE)$(USRLIB.$(BITS))
CPPFLAGS += -I$(EOG_BASE)/usr/include/eog-3.0

LIBCHAMPLAIN_BASE = $(WS_COMPONENTS)/gnome/libchamplain/build/prototype/$(MACH)
PKG_CONFIG_PATHS += $(LIBCHAMPLAIN_BASE)$(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS += -L$(LIBCHAMPLAIN_BASE)$(USRLIB.$(BITS))
CPPFLAGS += -I$(LIBCHAMPLAIN_BASE)/usr/include/libchamplain-0.12 -I$(LIBCHAMPLAIN_BASE)/usr/include/libchamplain-gtk-0.12

# Work around pkgdepend bug which doesn't resolve dependencies from
# the local workspace repo.
DEPENDED += $(WS_TOP)/components/gnome/eog/build/manifest-$(MACH)-eog.depend
DEPENDED += $(WS_TOP)/components/gnome/libchamplain/build/manifest-$(MACH)-libchamplain.depend

# Temporary until dependencies are all on build machines
REQUIRED_PACKAGES += $(shell $(GSED) -n 's/REQUIRED_PACKAGES +=//p' ../eog/Makefile)
REQUIRED_PACKAGES += $(shell $(GSED) -n 's/REQUIRED_PACKAGES +=//p' ../libchamplain/Makefile)
#end Delete

REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/clutter/clutter-gtk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libchamplain
REQUIRED_PACKAGES += library/desktop/libgdata
REQUIRED_PACKAGES += library/exempi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-desktop
REQUIRED_PACKAGES += library/desktop/libpeas
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
