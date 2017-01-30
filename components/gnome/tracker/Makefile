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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		64_and_32
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tracker
COMPONENT_VERSION=	1.6.0
COMPONENT_ARCHIVE_HASH= \
	sha256:7e2729627224f43f8cd99c18d027a3b984e049fe924a265a9b31857566c9e28a
COMPONENT_BUGDB=        gnome/libraries

TPNO=			25835

# Needs gobject-introspection, not available in S11
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

CFLAGS += $(XPG6MODE)

CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"

CONFIGURE_OPTIONS += --disable-libstemmer
CONFIGURE_OPTIONS += --disable-maemo
CONFIGURE_OPTIONS += --disable-schemas-compile
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-upower
CONFIGURE_OPTIONS += --enable-artwork
CONFIGURE_OPTIONS += --enable-cfg-man-pages
CONFIGURE_OPTIONS += --enable-dvi
CONFIGURE_OPTIONS += --enable-generic-media-extractor=gstreamer
# Disabled for now because of errors
#CONFIGURE_OPTIONS += --enable-gtk-doc
CONFIGURE_OPTIONS += --enable-hal
CONFIGURE_OPTIONS += --enable-icon
CONFIGURE_OPTIONS += --enable-icu-charset-detection
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-journal
CONFIGURE_OPTIONS += --enable-libexif
CONFIGURE_OPTIONS += --enable-libflac
CONFIGURE_OPTIONS += --enable-libgsf
CONFIGURE_OPTIONS += --enable-libgxps
CONFIGURE_OPTIONS += --enable-libjpeg
CONFIGURE_OPTIONS += --enable-libmediaart
CONFIGURE_OPTIONS += --enable-libpng
CONFIGURE_OPTIONS += --enable-libtiff
CONFIGURE_OPTIONS += --enable-libvorbis
CONFIGURE_OPTIONS += --enable-libxml2
CONFIGURE_OPTIONS += --enable-miner-apps
CONFIGURE_OPTIONS += --enable-miner-fs
CONFIGURE_OPTIONS += --enable-miner-user-guides
CONFIGURE_OPTIONS += --enable-mp3
CONFIGURE_OPTIONS += --enable-nautilus-extension
CONFIGURE_OPTIONS += --enable-playlist
CONFIGURE_OPTIONS += --enable-poppler
CONFIGURE_OPTIONS += --enable-ps
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-taglib
CONFIGURE_OPTIONS += --enable-text
CONFIGURE_OPTIONS += --enable-tracker-fts
CONFIGURE_OPTIONS += --enable-tracker-needle
CONFIGURE_OPTIONS += --enable-tracker-preferences
CONFIGURE_OPTIONS += --enable-tracker-writeback
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --with-unicode-support=libicu
CONFIGURE_OPTIONS += --with-bash-completion-dir=/etc/bash_completion.d

# Required due to patches.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += codec/libogg
REQUIRED_PACKAGES += codec/libvorbis
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += desktop/pdf-viewer/poppler
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += gnome/file-manager/nautilus
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/taglib
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gstreamer-1
REQUIRED_PACKAGES += library/desktop/gstreamer-1/gst-plugins-base
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libgsf
REQUIRED_PACKAGES += library/exempi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/desktop/libgxps
REQUIRED_PACKAGES += library/gnome/libmediaart
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/media-player/totem-pl-parser
REQUIRED_PACKAGES += system/hal
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libdbus-glib
REQUIRED_PACKAGES += system/library/math
