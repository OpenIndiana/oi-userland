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
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2022, Andreas Wacknitz
#

BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			gcr
COMPONENT_MJR_VERSION=	3.38
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).1
COMPONENT_REVISION=	3
COMPONENT_SUMMARY=	A GNOME library for displaying certificates and crypto UI
COMPONENT_PROJECT_URL=	https://gitlab.gnome.org/GNOME/gcr/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:17fcaf9c4a93a65fb1c72b82643bb102c13344084687d5886ea66313868d9ec9
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://github.com/GNOME/gcr
COMPONENT_FMRI=			library/gnome/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --libexecdir="$(USRLIBDIR.$(BITS))"
CONFIGURE_OPTIONS += --localstatedir="$(VARDIR)"
CONFIGURE_OPTIONS += --sysconfdir="$(ETCDIR)"

# Assumes GNU xgettext in PATH.
CONFIGURE_ENV += PATH=$(PATH.gnu)
CONFIGURE_ENV += GLIB_COMPILE_SCHEMAS=/usr/bin/glib-compile-schemas

# Requires a reconf due to patch to autoconf and automake-related files.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

# We don't have introspection for 32-bit.
CONFIGURE_OPTIONS.32 += --enable-introspection=no
# Required for other components.
CONFIGURE_OPTIONS.64 += --enable-introspection
# Required for other components.
CONFIGURE_OPTIONS.64 += --enable-vala
# Fix 64-bit builds.
CONFIGURE_OPTIONS.64 += ac_cv_path_LIBGCRYPT_CONFIG=$(USRBINDIR64)/libgcrypt-config

LDFLAGS += -lsocket
LIBS	+= -lsocket

# gobject-introspection
COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

COMPONENT_TEST_ARGS= -k -i

# Build dependencies
REQUIRED_PACKAGES += crypto/gnupg
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/security/libgpg-error

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/p11-kit
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
