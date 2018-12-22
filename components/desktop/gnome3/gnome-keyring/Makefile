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
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-keyring
COMPONENT_MJR_VERSION=	3.28
COMPONENT_MNR_VERSION=	2
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	GNOME Keyring
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:81171b7d07211b216b4c9bb79bf2deb3deca18fe8d56d46dda1c4549b4a2646a
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Sessions
COMPONENT_FMRI=		gnome/gnome-keyring
COMPONENT_LICENSE=	GPLv2,LGPLv2
COMPONENT_LICENSE_FILE= gnome-keyring.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -fi )

PAM_MODULE_DIR.32 = $(USRLIBDIR)/security
PAM_MODULE_DIR.64 = $(PAM_MODULE_DIR.32)/$(MACH64)
PAM_MODULE_DIR = $(PAM_MODULE_DIR.$(BITS))

CONFIGURE_BINDIR.64 = $(CONFIGURE_PREFIX)/bin

# Overwrite files in /usr/bin
$(INSTALL_64):	$(INSTALL_32)

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

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gcr
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
