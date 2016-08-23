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
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		yelp
COMPONENT_VERSION=	3.18.0
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/Yelp
COMPONENT_ARCHIVE_HASH= \
	sha256:a8c201e520c87832d017439492e4343e957a90da5c6d85060e8dd3b28ffee72e
COMPONENT_BUGDB=        gnome/docviewer

TPNO=			24621

# gmake check works but produces no useful output
TEST_TARGET = $(SKIP_TEST)

# Needs updated glib2, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

# Needed due to patch to configure.ac.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

CONFIGURE_OPTIONS += --disable-schemas-compile
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-bz2
CONFIGURE_OPTIONS += --enable-lzma
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --with-pic

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/webkitgtk4
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += system/library/math
