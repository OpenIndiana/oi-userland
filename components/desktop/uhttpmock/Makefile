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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS = 		64_and_32
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER = 		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		uhttpmock
COMPONENT_VERSION=	0.5.0
COMPONENT_PROJECT_URL=	https://gitlab.com/uhttpmock/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:26da182a2db2579c5ba4dad9096d52099e0766228c295cfbaed6de4046f7d16e
COMPONENT_ARCHIVE_URL=	https://tecnocode.co.uk/downloads/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/uhttpmock

TPNO=			25615

# Enable after libsoup is installed on the build servers
TEST_TARGET= $(SKIP_TEST)

# Needs gobject-introspection, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

# Delete this when build servers are installed with an updated libsoup
SOUP_BASE = $(WS_COMPONENTS)/gnome/libsoup/build/prototype/$(MACH)
PKG_CONFIG_PATHS.32 += $(SOUP_BASE)/usr/lib/pkgconfig
PKG_CONFIG_PATHS.64 += $(SOUP_BASE)/usr/lib/$(MACH64)/pkgconfig/
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
CPPFLAGS += -I$(SOUP_BASE)/usr/include/libsoup-2.4 \
	    -I$(SOUP_BASE)/usr/include/libsoup-gnome-2.4
LD_OPTIONS.32 += -L $(SOUP_BASE)/usr/lib
LD_OPTIONS.64 += -L $(SOUP_BASE)/usr/lib/$(MACH64)
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

# end Delete

# Tell g-ir-scanner not to cache results in homedir of user running the build
COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gtk-doc
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-shared
# Required for other components.
CONFIGURE_OPTIONS += --enable-vala
CONFIGURE_OPTIONS += --with-pic

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
