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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#


BUILD_BITS=             64
COMPILER=               gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-shell-extensions
COMPONENT_VERSION=	3.18.2
COMPONENT_PROJECT_URL=  https://extensions.gnome.org
COMPONENT_ARCHIVE_HASH= \
	sha256:cc514ffc896ed8c04853a89cb8e97058f9d5518313becf7c92aea5210b8adf61
COMPONENT_ARCHIVE_URL=	http://download.gnome.org/sources/$(COMPONENT_NAME)/3.18/$(COMPONENT_ARCHIVE)

TPNO=			25492

TEST_TARGET = $(NO_TESTS)

# It's useless without gnome-shell which is not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

CONFIGURE_OPTIONS += --enable-extensions=all

CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += gnome/file-manager/nautilus
REQUIRED_PACKAGES += gnome/gnome-shell
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += gnome/window-manager/mutter
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/clutter
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-menus
