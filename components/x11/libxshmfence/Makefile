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

COMPONENT_NAME=    libxshmfence
COMPONENT_VERSION= 1.3
COMPONENT_FMRI =   x11/library/libxshmfence
COMPONENT_SUMMARY= Shared memory SyncFence synchronization primitive
COMPONENT_ARCHIVE_HASH=	sha256:b884300d26a14961a076fbebc762a39831cb75f92bed5ccf9836345b459220c7
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=  --localstatedir=/var
CONFIGURE_OPTIONS +=  --enable-shared=yes
CONFIGURE_OPTIONS +=  --enable-static=no
CONFIGURE_OPTIONS +=  --with-pic

ENV = /usr/bin/env -i

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
