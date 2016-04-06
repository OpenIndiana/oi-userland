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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		efl
COMPONENT_VERSION=	1.12.3
COMPONENT_FMRI=     	library/e/efl
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://enlightenment.org
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:db2186df0cdfddb067a13654fd057f2147e83f55e0ecd365437a131942f56cf7
COMPONENT_ARCHIVE_URL=	http://download.enlightenment.org/rel/libs/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPL,LGPL,BSD,SMALL
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_SUMMARY=      Enlightenment - Core libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL=0

CONFIGURE_OPTIONS+=	CFLAGS="$(CFLAGS) -D__EXTENSIONS__"
CONFIGURE_OPTIONS+=	--enable-fribidi
CONFIGURE_OPTIONS+=	--with-opengl=full
# OpenGL ES 2.0 headers marked not present if x11/library/mesa not installed
CONFIGURE_OPTIONS+=	--enable-lua-old
CONFIGURE_OPTIONS+=	--disable-pulseaudio # Not packaged
CONFIGURE_OPTIONS+=	--disable-physics # Disable physics since bullet is missing
CONFIGURE_OPTIONS+=	--enable-gstreamer # Select series 0.10 over 1.0
CONFIGURE_OPTIONS+=	--disable-gstreamer1 # Select series 0.10 over 1.0
CONFIGURE_OPTIONS+=	--disable-doc # Broken in 1.8.2
CONFIGURE_OPTIONS+=     --enable-i-really-know-what-i-am-doing-and-that-this-will-probably-break-things-and-i-will-fix-them-myself-and-send-patches-aba


# Need to regenerate configure and Makefiles as 1.14 is used.
# COMPONENT_PRE_CONFIGURE_ACTION= pushd $(SOURCE_DIR); automake && autoconf; popd;

# Need to cleanup the configure since EINA_HAVE_BYTESWAP_H is not set properly
COMPONENT_POST_CONFIGURE_ACTION=$(RM) $(SOURCE_DIR)/src/lib/eina/eina_config.h;

# pkgdepend fails to resolve the python version if env is used
COMPONENT_POST_INSTALL_ACTION=sed -i -e '1 s|^.*$$|\#!/usr/bin/python$(PYTHON_VERSION)|' $(PROTO_DIR)/usr/bin/eina-bench-cmp;

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =    $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk

