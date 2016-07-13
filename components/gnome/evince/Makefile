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
COMPONENT_VERSION=	3.16.0
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/Evince
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:5138e2d05ccfe5e40df0c840b34f334c1f2bc03e5456aa954e64673d504ccd04
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/3.16/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/evince
TPNO=			25616

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

# Prevent libtool from embedding runpath (via -R) and other such annoyances.
COMPONENT_POST_CONFIGURE_ACTION += \
	(cd $(BUILD_DIR_$(BITS)) ; \
	$(GSED) -i \
	-e 's|hardcode_into_libs=yes|hardcode_into_libs=no|g' \
	-e 's|hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' \
	-e 's|need_relink=yes|need_relink=not_on_solaris|g' \
	libtool)


# For now, all things built for C++11 require gcc.
# Also, all components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER=gcc
CXXFLAGS += -std=c++11

# Delete this when build servers are installed with gnome-desktop
GNOME-DESKTOP_BASE = $(WS_COMPONENTS)/gnome/gnome-desktop/build/prototype/$(MACH)
PKG_CONFIG_PATHS.32 += $(GNOME-DESKTOP_BASE)/usr/lib/pkgconfig
PKG_CONFIG_PATHS.64 += $(GNOME-DESKTOP_BASE)/usr/lib/$(MACH64)/pkgconfig/
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
GNOME-DESKTOP_LD_OPTIONS.32 += -L$(GNOME-DESKTOP_BASE)/usr/lib
GNOME-DESKTOP_LD_OPTIONS.64 += -L$(GNOME-DESKTOP_BASE)/usr/lib/$(MACH64)
GNOME-DESKTOP_LD_OPTIONS += $(GNOME-DESKTOP_LD_OPTIONS.$(BITS))

# Delete this when build servers are installed with an updated libpoppler
POPPLER_BASE = $(WS_COMPONENTS)/desktop/poppler/build/prototype/$(MACH)
PKG_CONFIG_PATHS.32 += $(POPPLER_BASE)/usr/lib/pkgconfig
PKG_CONFIG_PATHS.64 += $(POPPLER_BASE)/usr/lib/$(MACH64)/pkgconfig/
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
POPPLER_LD_OPTIONS.32 += -L$(POPPLER_BASE)/usr/lib
POPPLER_LD_OPTIONS.64 += -L$(POPPLER_BASE)/usr/lib/$(MACH64)
POPPLER_LD_OPTIONS += $(POPPLER_LD_OPTIONS.$(BITS))

CPPFLAGS +=	"-I$(USRINCDIR)/libxml2"
LDFLAGS +=	$(CC_BITS) -lgmodule-2.0 -lm

CONFIGURE_ENV += LIBGNOME_DESKTOP_CFLAGS="-I$(GNOME-DESKTOP_BASE)/usr/include/gnome-desktop-3.0"
CONFIGURE_ENV += LIBGNOME_DESKTOP_LIBS="$(GNOME-DESKTOP_LD_OPTIONS) -lgnome-desktop-3"

CONFIGURE_ENV += POPPLER_CFLAGS="-I$(POPPLER_BASE)/usr/include/poppler/glib"
CONFIGURE_ENV += POPPLER_LIBS="$(POPPLER_LD_OPTIONS) -lpoppler-glib"

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

POPPLER_LIBDIR.32 += $(POPPLER_BASE)/usr/lib
POPPLER_LIBDIR.64 += $(POPPLER_BASE)/usr/lib/$(MACH64)
POPPLER_LIBDIR += $(POPPLER_LIBDIR.$(BITS))

# The poppler .la files in the poppler build prototype area have a libdir of
# /usr/lib. This confuses linking things where we are trying to get the
# poppler libraries from that prototype area.
COMPONENT_PRE_BUILD_ACTION += \
	$(RM) $(POPPLER_LIBDIR)/libpoppler.la \
	$(POPPLER_LIBDIR)/libpoppler-glib.la ;

REQUIRED_PACKAGES += archiver/unrar
REQUIRED_PACKAGES += desktop/pdf-viewer/poppler
REQUIRED_PACKAGES += gnome/file-manager/nautilus
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
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
