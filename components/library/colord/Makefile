#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2026 isoriano1968
#

# colord 1.4.7 as in Solaris 11.4 (solaris-userland components/desktop/colord
# @9d7a655): no gusb, gudev or libudev (Solaris patches 03-07), daemon run
# by SMF as user daemon.  OpenIndiana differences:
#   - 64-bit only (mutter, gnome-settings-daemon and g-c-c are 64-bit);
#   - no vala bindings (nothing in the GNOME 45 stack needs colord.vapi);
#   - Solaris' -fstack-protector-all and its 08-lssp patch left out;
#   - 07 without the <lcms/lcms2.h> hunk (OI's lcms2.pc points at
#     /usr/include/lcms2).

BUILD_BITS=		64
BUILD_STYLE=		meson

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		colord
COMPONENT_VERSION=	1.4.7
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/software/colord/
COMPONENT_SUMMARY=	colord - color management daemon and library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:de02d9910634ae159547585cec414e450f711c27235453b4f9b38a9f2361a653
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		service/image/colord
COMPONENT_CLASSIFICATION=	System/Hardware
COMPONENT_LICENSE=	GPL-2.0-or-later AND LGPL-2.1-or-later
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

# Self tests need a running system bus and colord; Solaris skips them too.
TEST_TARGET=		$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CFLAGS +=		-std=gnu99 -D__EXTENSIONS__
# (Solaris links with -z gnu-version-script-compat, which illumos ld lacks:
# see patches/10-version-script-illumos.patch.)

CONFIGURE_OPTIONS +=	--libexecdir=$(USRLIBEXECDIR)
CONFIGURE_OPTIONS +=	--localstatedir=$(VARDIR)
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS +=	-Ddaemon=true
CONFIGURE_OPTIONS +=	-Ddaemon_user=daemon
CONFIGURE_OPTIONS +=	-Dsystemd=false
CONFIGURE_OPTIONS +=	-Dudev_rules=false
CONFIGURE_OPTIONS +=	-Dbash_completion=false
CONFIGURE_OPTIONS +=	-Dargyllcms_sensor=false
CONFIGURE_OPTIONS +=	-Dlibcolordcompat=false
CONFIGURE_OPTIONS +=	-Dsane=false
CONFIGURE_OPTIONS +=	-Dintrospection=true
CONFIGURE_OPTIONS +=	-Dvapi=false
CONFIGURE_OPTIONS +=	-Dman=false
CONFIGURE_OPTIONS +=	-Ddocs=false
CONFIGURE_OPTIONS +=	-Dtests=false
CONFIGURE_OPTIONS +=	-Dpnp_ids=/usr/share/hwdata/pci.ids

CONFIGURE_ENV +=	PATH="$(GNUBIN):$(PATH)"

# SMF service (runs colord as daemon; colord stays in the foreground).
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -D -m 0444 $(COMPONENT_DIR)/files/colord.xml \
	    $(PROTO_DIR)/lib/svc/manifest/system/colord.xml ;

# Build dependencies
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection

# Dependencies (SUNWcs: the SMF milestones; hardware-registry: pci.ids)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += system/data/hardware-registry
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library/polkit
