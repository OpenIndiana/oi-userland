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
COMPONENT_VERSION= 1.3.2
COMPONENT_SUMMARY= Shared memory SyncFence synchronization primitive
COMPONENT_ARCHIVE_EXTENSION= .tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:870df257bc40b126d91b5a8f1da6ca8a524555268c50b59c0acd1a27f361606f
COMPONENT_FMRI =   x11/library/libxshmfence
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS +=  --localstatedir=/var
CONFIGURE_OPTIONS +=  --enable-shared=yes
CONFIGURE_OPTIONS +=  --enable-static=no
CONFIGURE_OPTIONS +=  --with-pic

ENV = /usr/bin/env -i

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
