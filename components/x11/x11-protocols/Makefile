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
# Copyright 2015 Alexander Pyhalov
# Copyright 2019 Aurelien Larcher
#
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= xorgproto
COMPONENT_VERSION= 2024.1
COMPONENT_REVISION= 1
COMPONENT_FMRI= x11/header/x11-protocols
COMPONENT_SUMMARY= X Window System protocol definitions
COMPONENT_CLASSIFICATION= Development/X11
OMPONENT_PROJECT_URL= $(XORG_PROJECT_URL)
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:372225fd40815b8423547f5d890c5debc72e88b91088fbfb13158c20495ccb59
COMPONENT_ARCHIVE_URL= $(XORG_PROTO_BASE_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= MIT

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION +=( cd $(@D); autoreconf -fiv );

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --without-xmlto
CONFIGURE_OPTIONS+= --without-fop
CONFIGURE_OPTIONS+= --localstatedir=/var
CONFIGURE_OPTIONS+= --enable-legacy

COMPONENT_INSTALL_ARGS += pkgconfigdir=/usr/share/pkgconfig

# Build dependencies
REQUIRED_PACKAGES += developer/build/autoconf/xorg-macros

# Auto-generated dependencies
