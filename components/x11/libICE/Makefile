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

COMPONENT_NAME=    libICE
COMPONENT_VERSION= 1.1.2
COMPONENT_FMRI =   x11/library/libice
COMPONENT_SUMMARY= libICE - Inter-Client Exchange Library
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH= sha256:974e4ed414225eb3c716985df9709f4da8d22a67a2890066bc6dfc89ad298625
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=  --enable-shared=yes
CONFIGURE_OPTIONS +=  --enable-static=no
CONFIGURE_OPTIONS +=  --enable-unix-transport
CONFIGURE_OPTIONS +=  --enable-tcp-transport
CONFIGURE_OPTIONS +=  --disable-local-transport
CONFIGURE_OPTIONS +=  --enable-ipv6

LD_OPTIONS += -M$(COMPONENT_DIR)/mapfile-vers

# Build dependencies
REQUIRED_PACKAGES += x11/library/xtrans

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
