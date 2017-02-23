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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		64
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		file-roller
COMPONENT_VERSION=	3.20.4
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Apps/FileRoller
COMPONENT_ARCHIVE_HASH= \
	sha256:d9346bb90d5f3296bf22f93a81f5bcd2e974620a4d81efea882db2b3db3b66c1
COMPONENT_BUGDB=	gnome/libraries
COMPONENT_ANITYA_ID=	5392

TPNO=			32830

TEST_TARGET = $(NO_TESTS)

# Needs gtk3, not available in S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# Use the GNOME 3 libnotify even though the GNOME 2 one is still the default
PKG_CONFIG_PATHS.32 += $(PKG_CONFIG_PATH.32)/libnotify-4
PKG_CONFIG_PATHS.64 += $(PKG_CONFIG_PATH.64)/libnotify-4
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.32 += -L $(USRLIB.32)/libnotify-4 -R $(USRLIB.32)/libnotify-4
LD_OPTIONS.64 += -L $(USRLIB.64)/libnotify-4 -R $(USRLIB.64)/libnotify-4
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

CONFIGURE_OPTIONS += --enable-libarchive
CONFIGURE_OPTIONS += --disable-static

# Assumes GNU xgettext in PATH
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

REQUIRED_PACKAGES += gnome/file-manager/nautilus
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libnotify
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/json-glib
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += system/library/math
