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

BUILD_BITS =            64
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		folks
COMPONENT_VERSION=	0.11.1
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Folks
COMPONENT_ARCHIVE_HASH= \
	sha256:6740d9074be911959904b40e7264d298bb5622995098ddfa1751dcd2bc4c917d
COMPONENT_BUGDB=        gnome/libraries
COMPONENT_ANITYA_ID=	13121

TPNO=			25282

# Tests do not yet work with Userland framework
TEST_TARGET = $(SKIP_TEST)

# Needs gobject-introspection, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# __EXTENSIONS__ required for various non-standard function usages.
CFLAGS += -D__EXTENSIONS__
# Not compiled as an xpg6 application, but configure defines this, so we
# override and undefine it to avoid feature_tests.h failures; unclear what the
# correct fix is.
CFLAGS += -U_POSIX_SOURCE

# A pkg-config file isn't shipped in Solaris for nss/nspr 64-bit, so we
# workaround this by using the one-off copy in the evolution-data-server
# component directory
PKG_CONFIG_PATHS.64 += $(WS_COMPONENTS)/gnome/evolution-data-server
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))

CONFIGURE_ENV += PATH="$(GNUBIN):$(PATH)"

# Requires valadoc.
CONFIGURE_OPTIONS += --disable-docs
CONFIGURE_OPTIONS += --disable-schemas-compile
CONFIGURE_OPTIONS += --disable-static
# Linux-specific bluetooth support.
CONFIGURE_OPTIONS += --disable-bluez-backend
# GSM Telephony Support (unnecessary).
CONFIGURE_OPTIONS += --disable-ofono-backend
# Not currently shipping libsocialweb (https://github.com/GNOME/libsocialweb).
CONFIGURE_OPTIONS += --disable-libsocialweb-backend
# Not currently shipping zeitgeist (http://zeitgeist-project.com/), so disable
# support.
CONFIGURE_OPTIONS += --disable-zeitgeist
CONFIGURE_OPTIONS += --enable-eds-backend
CONFIGURE_OPTIONS += --enable-import-tool
CONFIGURE_OPTIONS += --enable-inspect-tool
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-telepathy-backend
# Required for other components.
CONFIGURE_OPTIONS += --enable-tracker-backend
# Required for other components.
CONFIGURE_OPTIONS += --enable-vala
CONFIGURE_OPTIONS += --with-pic
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR)

# Requires tracker and evolution data server be installed on the build servers

REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/evolution-data-server
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/libgee
REQUIRED_PACKAGES += library/desktop/search/tracker
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += library/telepathy-glib
