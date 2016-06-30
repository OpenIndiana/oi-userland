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

BUILD_BITS =            64_and_32
# All components using gobject-introspection must be built with gcc as
# gobject-introspection does not produce correct results when using Studio.
COMPILER =              gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		grilo
COMPONENT_VERSION=	0.2.14
COMPONENT_ARCHIVE_HASH= \
	sha256:79c82ea1747ae7430a648aa9660e44d88d48c968bcdaeb3b2c5cb97e1c921ccd
COMPONENT_BUGDB=        gnome/multimedia

TPNO=			25361

# Tests don't seem to do anything - 23712784
TEST_TARGET = $(SKIP_TEST)

# Needs gobject-introspection, not available on S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/gnome-component.mk

# Assumes GNU xgettext in PATH
CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)

CONFIGURE_OPTIONS += --disable-debug
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gtk-doc
# Required for other components.
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-grl-net
CONFIGURE_OPTIONS += --enable-grl-pls
CONFIGURE_OPTIONS += --enable-shared
# Required for other components.
CONFIGURE_OPTIONS += --enable-vala
CONFIGURE_OPTIONS += --with-pic

# Delete when build servers are installed with an updated totem-pl-parser
TPP_BASE = $(WS_COMPONENTS)/gnome/totem-pl-parser/build/prototype/$(MACH)
PKG_CONFIG_PATHS.32 += $(TPP_BASE)/usr/lib/pkgconfig/
PKG_CONFIG_PATHS.64 += $(TPP_BASE)/usr/lib/$(MACH64)/pkgconfig/
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))

LD_OPTIONS.32 += -L $(TPP_BASE)/usr/lib
LD_OPTIONS.64 += -L $(TPP_BASE)/usr/lib/$(MACH64)
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

CONFIGURE_ENV += TOTEM_PL_PARSER_CFLAGS="-I$(TPP_BASE)/usr/include/totem-pl-parser/1/plparser"

# Work around pkgdepend bug which doesn't resolve dependencies from
# the local workspace repo.
DEPENDED += $(WS_TOP)/components/gnome/totem-pl-parser/build/manifest-$(MACH)-totem-pl-parser.depend

# Temporary until dependencies are all on build machines
REQUIRED_PACKAGES += $(shell $(GSED) -n 's/REQUIRED_PACKAGES +=//p' ../totem-pl-parser/Makefile)
#end Delete


REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/media-player/totem-pl-parser
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
