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
# Copyright 2015 Aurelien Larcher
#

X11_CATEGORY=APP
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=           luit
COMPONENT_VERSION=        1.1.1
COMPONENT_REVISION=       1
COMPONENT_FMRI=           terminal/luit
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SUMMARY=  luit - Locale and ISO 2022 support for Unicode terminals
COMPONENT_ARCHIVE_HASH= \
  sha256:30b0e787cb07a0f504b70f1d6123930522111ce9d4276f6683a69b322b49c636

include $(WS_MAKE_RULES)/common.mk

PKG_CONFIG_PATH+=:$(USRSHAREDIR)/pkgconfig
LD_OPTIONS+= -L$(XORG_LIBDIR.$(BITS)) -R$(XORG_LIBDIR.$(BITS))

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libfontenc
