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

BUILD_BITS =            64_and_32
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
# Additionally, colord requires support for __attribute__(cleanup), which
# Studio does not yet support until 12.5 (ER 17630845).
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		colord
COMPONENT_VERSION=	1.1.8
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/software/colord/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
	sha256:f03e951641f39c2cea6ce7a6435608dd2bc0bd2c98e901ae331193f95f3e8907
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/libraries

TPNO=			25612

TEST_TARGET = $(NO_TESTS)

# Needs gobject-introspection, not available on S11.
include $(WS_MAKE_RULES)/no-evaluation.mk

include $(WS_MAKE_RULES)/gnome-component.mk

# Requires fpclassify (c99).
CFLAGS += -std=gnu99

# Required due to patches.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv; intltoolize --force);

# Make sure we haven't broken the SMF manifest formatting
COMPONENT_PREP_ACTION += \
    ( /usr/sbin/svccfg validate $(COMPONENT_DIR)/files/colord.xml );

# Requires external package (https://bash-completion.alioth.debian.org) that we
# don't currently have in Solaris.
CONFIGURE_OPTIONS += --disable-bash-completion
# gusb appears to be an abandoned project.
CONFIGURE_OPTIONS += --disable-gusb
CONFIGURE_OPTIONS += --enable-polkit
CONFIGURE_OPTIONS += --disable-static
# Linux-specific.
CONFIGURE_OPTIONS += --disable-systemd-login
# Linux-specific.
CONFIGURE_OPTIONS += --disable-udev
CONFIGURE_OPTIONS += --enable-gtk-doc
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-shared
# Required for other components.
CONFIGURE_OPTIONS += --enable-vala
# may need tweaking to give colord user sufficient rights
CONFIGURE_OPTIONS += --with-daemon-user=daemon
CONFIGURE_OPTIONS += --with-pic
# Mostly a placebo value; udev support is disabled above, but it still delivers
# 'rule' files for udev (omitted from package manifest).
CONFIGURE_OPTIONS += --with-udevrulesdir=/etc/udev/rules.d

# Assumes GNU xgettext and tail in PATH
COMPONENT_BUILD_ENV += PATH=$(GNUBIN):$(PATH)
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

# Tell g-ir-scanner not to cache results in homedir of user running the build
COMPONENT_BUILD_ENV += GI_SCANNER_DISABLE_CACHE=""

REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/core-os
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/polkit
