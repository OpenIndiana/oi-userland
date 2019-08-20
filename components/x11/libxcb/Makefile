#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2013, Aurelien Larcher. All rights reserved.
#

X11_CATEGORY=LIB
include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/x11.mk

COMPONENT_NAME=        libxcb
COMPONENT_VERSION=     1.13
COMPONENT_FMRI=        x11/library/libxcb
COMPONENT_SUMMARY=     The X protocol C-language Binding (XCB): Libraries
COMPONENT_PROJECT_URL= http://xcb.freedesktop.org
COMPONENT_ARCHIVE_HASH=	\
  sha256:188c8752193c50ff2dbe89db4554c63df2e26a2e47b0fa415a70918b5b851daa
COMPONENT_ARCHIVE_URL=	  $(COMPONENT_PROJECT_URL)/dist/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --enable-shared
CONFIGURE_OPTIONS+= --disable-libtool-lock 
CONFIGURE_OPTIONS+= --enable-devel-docs=no 
CONFIGURE_OPTIONS+= --enable-composite 
CONFIGURE_OPTIONS+= --enable-damage 
CONFIGURE_OPTIONS+= --enable-dpms 
CONFIGURE_OPTIONS+= --enable-dri2 
CONFIGURE_OPTIONS+= --enable-glx 
CONFIGURE_OPTIONS+= --enable-randr 
CONFIGURE_OPTIONS+= --enable-record 
CONFIGURE_OPTIONS+= --enable-render 
CONFIGURE_OPTIONS+= --enable-resource 
CONFIGURE_OPTIONS+= --enable-screensaver 
CONFIGURE_OPTIONS+= --enable-shape 
CONFIGURE_OPTIONS+= --enable-shm 
CONFIGURE_OPTIONS+= --enable-sync 
CONFIGURE_OPTIONS+= --enable-xevie 
CONFIGURE_OPTIONS+= --enable-xfixes 
CONFIGURE_OPTIONS+= --enable-xfree86-dri 
CONFIGURE_OPTIONS+= --enable-xinerama 
CONFIGURE_OPTIONS+= --enable-xinput 
CONFIGURE_OPTIONS+= --enable-xprint 
CONFIGURE_OPTIONS+= --disable-selinux 
CONFIGURE_OPTIONS+= --enable-xtest 
CONFIGURE_OPTIONS+= --enable-xv 
CONFIGURE_OPTIONS+= --enable-xvmc 
CONFIGURE_OPTIONS+= --with-queue-size=32768 
CONFIGURE_OPTIONS+= --with-pic

# Build dependencies
REQUIRED_PACKAGES += developer/check
REQUIRED_PACKAGES += x11/header/xcb-protocols
REQUIRED_PACKAGES += x11/library/libpthread-stubs

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxdmcp
