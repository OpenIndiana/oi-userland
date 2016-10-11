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

BUILD_BITS=		32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libxklavier
COMPONENT_VERSION=	5.0
COMPONENT_PROJECT_URL=	http://freedesktop.org/wiki/Software/LibXklavier/
COMPONENT_ARCHIVE_HASH=	\
    sha256:30e572d3bac0f4c8ba0098dd63527a789cb85649bd4c8d5ffd8d1f34306e36d1
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/gswitchit/files/libxklavier/5.0/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/libraries

TPNO=			3429

# Tests do not work in userland framework yet
TEST_TARGET = $(SKIP_TEST)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION += (cd $(@D) ; autoreconf -fiv )

# Need to ensure GNU cp is first in $PATH to avoid
# "cp: illegal option -- u" errors installing the docs
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-gtk-doc
CONFIGURE_OPTIONS += --enable-xkb-support
CONFIGURE_OPTIONS += --with-xkb-base=/usr/share/X11/xkb

REQUIRED_PACKAGES += data/iso-codes
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += x11/keyboard/data-xkb
REQUIRED_PACKAGES += x11/keyboard/xkbcomp
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxkbfile
