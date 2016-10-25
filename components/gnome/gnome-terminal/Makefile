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

BUILD_BITS=		64
COMPILER=		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-terminal
COMPONENT_VERSION=	3.18.2
COMPONENT_PROJECT_URL=  https://wiki.gnome.org/Apps/Terminal
COMPONENT_ARCHIVE_HASH= \
	sha256:5e35c0fa1395258bab83952cfabe4c1828b8655bcd761f8faed70b452bd89efa
COMPONENT_BUGDB=        gnome/terminal

TPNO=			25405

include $(WS_MAKE_RULES)/gnome-component.mk

# Need to regenerate configure after stack-protector.patch edits configure.ac
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

CONFIGURE_ENV += PATH=$(GNUBIN):$(PATH)
COMPONENT_BUILD_ENV += PATH="$(GNUBIN):$(PATH)"

CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR)

# Force use of gnutls-3 pkgconfig during 2.x->3.x transition
PKG_CONFIG_PATHS.32 += /usr/lib/pkgconfig/gnutls-3
PKG_CONFIG_PATHS.64 += /usr/lib/$(MACH64)/pkgconfig/gnutls-3
PKG_CONFIG_PATHS += $(PKG_CONFIG_PATHS.$(BITS))
LD_OPTIONS.32 += -L /usr/lib/gnutls-3 -R /usr/lib/gnutls-3
LD_OPTIONS.64 += -L /usr/lib/$(MACH64)/gnutls-3 -R /usr/lib/$(MACH64)/gnutls-3
LD_OPTIONS += $(LD_OPTIONS.$(BITS))

# uuid detection fails due to Solaris bug 15586738, use local uuid.pc to avoid
PKG_CONFIG_PATHS  += $(COMPONENT_DIR)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-introspection
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-migration
CONFIGURE_OPTIONS += --enable-nautilus-extension

unexport SHELLOPTS

REQUIRED_PACKAGES += gnome/file-manager/nautilus
REQUIRED_PACKAGES += gnome/gnome-shell
REQUIRED_PACKAGES += gnome/gsettings-desktop-schemas
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/dconf
REQUIRED_PACKAGES += library/gnome/vte3
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
