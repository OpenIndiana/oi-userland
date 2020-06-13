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

#
# Copyright (c) 2013-2017, Aurelien Larcher. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS= 64
BUILD_STYLE= meson
NEED_LIBJPEG_FLAGS=yes
USE_GIT_SHALLOW_CLONE=yes
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		efl
COMPONENT_VERSION=	1.24.2
COMPONENT_SUMMARY=	Enlightenment Foundation Libraries
COMPONENT_FMRI=		library/e/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_PROJECT_URL=	http://www.enlightenment.org
GIT_REPO=		https://git.enlightenment.org/core/efl.git
GIT_BRANCH=		master
#COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
#COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
#COMPONENT_ARCHIVE_HASH= \
	sha256:56f02aa6b2c4ca0252fb6547fa8d2fdfff842e245a93ae41adca7a191900bf73
#COMPONENT_ARCHIVE_URL= \
	http://download.enlightenment.org/rel/libs/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD 2-clause, GPLv2, LGPLv2.1, Small

include $(WS_MAKE_RULES)/common.mk

gcc_OPT = -Og -g3 -ggdb3 -pipe

MESON_BUILDTYPE=debug
CONFIGURE_OPTIONS+= -Dlua-interpreter=lua
CONFIGURE_OPTIONS+= -Dv4l2=false
CONFIGURE_OPTIONS+= -Dlibmount=false
CONFIGURE_OPTIONS+= -Deeze=false
CONFIGURE_OPTIONS+= -Devas-loaders-disabler=json
CONFIGURE_OPTIONS+= -Decore-imf-loaders-disabler=xim,ibus,scim

CONFIGURE_ENV += PYTHON=$(PYTHON)

# Build dependencies
REQUIRED_PACKAGES += x11/library/mesa

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libraw
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/audio/gstreamer1
REQUIRED_PACKAGES += library/audio/gstreamer1/plugin/base
REQUIRED_PACKAGES += library/bullet
REQUIRED_PACKAGES += library/c++/harfbuzz
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/giflib
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/libspectre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcomposite
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/libxdamage
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxfixes
REQUIRED_PACKAGES += x11/library/libxi
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxrandr
REQUIRED_PACKAGES += x11/library/libxrender
REQUIRED_PACKAGES += x11/library/libxscrnsaver
REQUIRED_PACKAGES += x11/library/libxtst
