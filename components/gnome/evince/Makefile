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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		evince
COMPONENT_VERSION=	3.21.4
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/Evince
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:12f0a411380b476a540a9e0629ca8ca938dad5e787e4ed1ff4f467e0356b1ffd
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/3.21/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/evince
TPNO=			30508

TEST_TARGET= $(NO_TESTS)

# Needs other components that are not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

# Need to pick up the GNU version of xgettext.
PATH=$(GNUBIN):$(USRBINDIR)

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; \
	libtoolize --force --copy ; \
	intltoolize --force --copy --automake ; \
	aclocal -I . ; \
	autoheader ; \
	automake -a -c -f ; \
	autoconf )

# For now, all things built for C++11 require gcc.
# Also, all components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER=gcc
CXXFLAGS += -std=c++11

CPPFLAGS +=	"-I$(USRINCDIR)/libxml2"
LDFLAGS +=	$(CC_BITS) -lgmodule-2.0 -lm

CONFIGURE_OPTIONS +=	--libexecdir="$(USRLIB)"
CONFIGURE_OPTIONS +=	--sysconfdir="$(ETCDIR)"

# Browser plugins of any form are obsolete at this point.
CONFIGURE_OPTIONS +=	--disable-browser-plugin
# Requires djvulibre library.
CONFIGURE_OPTIONS +=	--disable-djvu
# Requires LaTeX libraries.
CONFIGURE_OPTIONS +=	--disable-dvi
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-comics
CONFIGURE_OPTIONS +=	--enable-dbus
# Required for other components.
CONFIGURE_OPTIONS +=	--enable-introspection
CONFIGURE_OPTIONS +=	--enable-libgnome-desktop
# Re-enable when all of the new GNOME 3 desktop is integrated.
CONFIGURE_OPTIONS +=	--disable-nautilus
CONFIGURE_OPTIONS +=	--enable-pdf
CONFIGURE_OPTIONS +=	--enable-previewer
CONFIGURE_OPTIONS +=	--enable-ps
CONFIGURE_OPTIONS +=	--enable-shared
CONFIGURE_OPTIONS +=	--enable-t1lib
CONFIGURE_OPTIONS +=	--enable-thumbnailer
CONFIGURE_OPTIONS +=	--enable-tiff
CONFIGURE_OPTIONS +=	--enable-viewer
CONFIGURE_OPTIONS +=	--enable-xps

# Always show the build and link lines for easier debugging.
COMPONENT_BUILD_ARGS += V=1

# Needed to find GNU msgfmt.
COMPONENT_BUILD_ENV += PATH="/usr/gnu/bin:$(PATH)"

REQUIRED_PACKAGES += archiver/unrar
REQUIRED_PACKAGES += desktop/pdf-viewer/poppler
REQUIRED_PACKAGES += gnome/file-manager/nautilus
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gstreamer-1
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-base
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libgxps
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-desktop
REQUIRED_PACKAGES += library/gnome/libsecret
REQUIRED_PACKAGES += library/libspectre
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/perl-5/xml-parser
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
