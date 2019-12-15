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
# Copyright 2013 Andrzej Szeszo.  All rights reserved.
# Copyright 2016-2019 Aurelien Larcher. All rights reserved.
#

BUILD_BITS=32
include ../../../make-rules/shared-macros.mk

COMPONENT_VERSION= 7.5.0
ILLUMOS_GCC_REVISION= 0
COMPONENT_SRC_NAME= gcc-$(COMPONENT_VERSION)-oi-$(ILLUMOS_GCC_REVISION)
COMPONENT_SRC= gcc-$(COMPONENT_SRC_NAME)
COMPONENT_ARCHIVE= $(COMPONENT_SRC_NAME).tar.gz
COMPONENT_ARCHIVE_URL= \
  https://github.com/OpenIndiana/gcc/archive/$(COMPONENT_ARCHIVE)

COMPONENT_ARCHIVE_HASH= \
  sha256:24e3f9dd8348b9172015bc50be9fb5af0403f9eff97cc21066df8d722e1710db

MPFR_VERSION=4.0.2
MPFR_ARCHIVE_HASH= \
  sha256:c05e3f02d09e0e9019384cdd58e0f19c64e6db1fd6f5ecf77b4b1c61ca253acc

MPC_VERSION=1.1.0
MPC_ARCHIVE_HASH= \
  sha256:6985c538143c1208dcb1ac42cedad6ff52e267b47e5f970183a3e75125b43c2e

GMP_VERSION=6.1.2
GMP_ARCHIVE_HASH= \
  sha256:5275bb04f4863a13516b2f39392ac5e272f5e1bb8057b18aec1c9b79d73d8fb2


include $(WS_MAKE_RULES)/gcc-component.mk

CONFIGURE_OPTIONS+= --enable-plugins
CONFIGURE_OPTIONS+= --enable-objc-gc
CONFIGURE_OPTIONS+= --enable-initfini-array
CONFIGURE_OPTIONS+= --enable-languages=c,c++,fortran,lto,objc
CONFIGURE_OPTIONS+= --disable-libitm
CONFIGURE_OPTIONS+= enable_frame_pointer=yes

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gc

