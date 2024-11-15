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
#

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME= xtrans
COMPONENT_VERSION= 1.5.2
COMPONENT_SUMMARY= xtrans - X network protocol transport layer development files
COMPONENT_FMRI=    x11/library/$(COMPONENT_NAME)
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:5c5cbfe34764a9131d048f03c31c19e57fb4c682d67713eab6a65541b4dff86c
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)

COMPONENT_INSTALL_ARGS += pkgconfigdir=/usr/share/pkgconfig

# Auto-generated dependencies
