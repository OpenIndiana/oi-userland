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
# Copyright 2024 Friedrich Kink
#

USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zbar
COMPONENT_VERSION=	0.23.93
COMPONENT_DESCRIPTION=	ZBar is an open source software suite for reading bar codes from \
			various sources, including webcams.
COMPONENT_SUMMARY=	ZBAR  bar code reader
COMPONENT_PROJECT_URL=	https://github.com/mchehab/zbar
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:212dfab527894b8bcbcc7cd1d43d63f5604a07473d31a5f02889e372614ebe28
COMPONENT_ARCHIVE_URL=	https://github.com/mchehab/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		image/zbar
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=	LGPL2.1
COMPONENT_LICENSE_FILE=	COPYING

# no usable tests available
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( cd $(@D) && autoreconf -vfi )

# configure
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-video
CONFIGURE_OPTIONS += --disable-dependency-tracking
CONFIGURE_OPTIONS += --enable-introspection=yes
CONFIGURE_OPTIONS += --with-gir
CONFIGURE_OPTIONS += --with-java=no
CONFIGURE_OPTIONS += --with-qt=no

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/imagemagick
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxv
