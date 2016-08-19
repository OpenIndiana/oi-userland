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

BUILD_BITS=		64
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gucharmap
COMPONENT_VERSION=	3.18.1
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Apps/Gucharmap
COMPONENT_ARCHIVE_HASH= \
	sha256:b286d09dcd7811e6678e3d5830970d310d5730f7be5657ec400295df0b36fa35
COMPONENT_BUGDB=        gnome/applications

TPNO=			25270

TEST_TARGET = $(NO_TESTS)

# Needs updated glib2, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_OPTIONS += --disable-Bsymbolic
CONFIGURE_OPTIONS += --disable-static
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-shared
# Required for other components.
CONFIGURE_OPTIONS += --enable-vala
CONFIGURE_OPTIONS += --with-gtk=3.0

# Assumes GNU msgfmt in PATH.
CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += developer/vala
# Build time requirement for desktop-file-validate until desktop-file-utils
# is split out of the control-center package
REQUIRED_PACKAGES += gnome/preferences/control-center
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
