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
# Copyright (c) 2013 David Hoeppner. All rights reserved.
# Copyright (c) 2018 Jason Martin
# Copyright (c) 2021 Andreas Wacknitz
#
BUILD_BITS=			32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=     libgee
COMPONENT_VERSION=  0.20.4
COMPONENT_SUMMARY=  GObject based collection and utility library
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Libgee
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:524c1bf390f9cdda4fbd9a47b269980dc64ab5280f0801b53bc69d782c72de0e
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/libgee/0.20/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			library/desktop/libgee
COMPONENT_CLASSIFICATION=	Development/GNOME and GTK+

# Since GLib 2.62, gtester and gtester-report are deprecated. Thus, disable tests until ported:
TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS  +=       --disable-static
CONFIGURE_OPTIONS  +=       --enable-shared

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
