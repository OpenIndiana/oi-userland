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
# Copyright 2016 Aurelien Larcher
#

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=    libXt
COMPONENT_VERSION= 1.2.1
COMPONENT_FMRI=    x11/library/toolkit/libxt
COMPONENT_SUMMARY= libXt - X Toolkit library
COMPONENT_ARCHIVE_HASH= \
  sha256:679cc08f1646dbd27f5e48ffe8dd49406102937109130caab02ca32c083a3d60

include $(WS_MAKE_RULES)/common.mk

# https://bugs.freedesktop.org/show_bug.cgi?id=6569
LD_B_DIRECT=

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i )

CPPFLAGS+= -DGETVALUES_BUG -DNO_ALLOCA

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libice
REQUIRED_PACKAGES += x11/library/libsm
REQUIRED_PACKAGES += x11/library/libx11
