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
# Copyright 2026 isoriano1968
#

BUILD_STYLE=		meson

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		evince
HUMAN_VERSION=		48.4
COMPONENT_SUMMARY=	Evince - GNOME document viewer
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/Evince
COMPONENT_ARCHIVE_HASH=	\
	sha256:f296c5c662886635d4cd597e8ac0afcde7982be4486533c2b7f095b268be8668
COMPONENT_FMRI=		desktop/pdf-viewer/evince
COMPONENT_CLASSIFICATION=	Applications/Office
COMPONENT_LICENSE=	GPL-2.0-or-later
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is expected
PATH=			$(PATH.gnu)

# no gi-docgen
CONFIGURE_OPTIONS +=	-Dgtk_doc=false
# PDF and PostScript, as Solaris 11.4
CONFIGURE_OPTIONS +=	-Ddjvu=disabled
CONFIGURE_OPTIONS +=	-Ddvi=disabled
CONFIGURE_OPTIONS +=	-Dxps=disabled
CONFIGURE_OPTIONS +=	-Dps=enabled
# spell checking for annotations; auto would depend on the build host
CONFIGURE_OPTIONS +=	-Dgspell=enabled

# update-desktop-database (meson.build requires it)
REQUIRED_PACKAGES += library/desktop/desktop-file-utils

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/accessibility/at-spi2-core
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/gstreamer/plugin/base
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gnome-desktop
REQUIRED_PACKAGES += library/desktop/gspell-3
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libhandy
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libsecret
REQUIRED_PACKAGES += library/libspectre
REQUIRED_PACKAGES += library/libsynctex
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
