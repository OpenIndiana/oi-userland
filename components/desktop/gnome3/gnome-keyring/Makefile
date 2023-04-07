#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2017 Alexander Pyhalov
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018 Michal Nowak
# Copyright (c) 2021 Andreas Wacknitz
# Copyright (c) 2023 Klaus Ziegler
#
BUILD_BITS= 64_and_32
USE_COMMON_TEST_MASTER= no
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-keyring
COMPONENT_MJR_VERSION=	3.36
COMPONENT_MNR_VERSION=	0
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_SUMMARY=	GNOME Keyring is a collection of components that store secrets, passwords, keys, certificates and make them available to applications
COMPONENT_PROJECT_URL=	https://www.gnome.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:a264b57a8d1a71fdf0d66e8cd6033d013fb828be279c35766545eb9bb3734f87
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Sessions
COMPONENT_FMRI=		gnome/gnome-keyring
COMPONENT_LICENSE=	GPLv2,LGPLv2

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -fi )

PAM_MODULE_DIR.32 = $(USRLIBDIR)/security
PAM_MODULE_DIR.64 = $(PAM_MODULE_DIR.32)/$(MACH64)
PAM_MODULE_DIR = $(PAM_MODULE_DIR.$(BITS))

CONFIGURE_ENV =	GLIB_COMPILE_SCHEMAS=/usr/bin/glib-compile-schemas

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --disable-selinux
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-gpg-agent
CONFIGURE_OPTIONS += --enable-pam
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-ssh-agent
CONFIGURE_OPTIONS += --with-pam-dir=$(PAM_MODULE_DIR)
CONFIGURE_OPTIONS += --with-pic
# Linux-specific capabilities support.
CONFIGURE_OPTIONS += --without-libcap-ng

COMPONENT_TEST_TRANSFORMS = \
	'-e "s|t create temporary file.*|t create temporary file|" ' \
	'-n ' \
	'-e "/TOTAL:/p" ' \
	'-e "/SKIP:/p" ' \
	'-e "/PASS:/p" ' \
	'-e "/FAIL:/p" ' \
	'-e "/ERROR:/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
