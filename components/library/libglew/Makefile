#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Jim Klimov <jimklimov@gmail.com>
#

BUILD_STYLE = justmake
DROP_STATIC_LIBRARIES = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		glew
COMPONENT_VERSION=	2.3.1
COMPONENT_SUMMARY=	The OpenGL Extension Wrangler Library
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_FMRI=		x11/library/lib$(COMPONENT_NAME)
COMPONENT_LICENSE=	BSD-3-Clause AND MIT
COMPONENT_LICENSE_FILE=	LICENSE.txt
COMPONENT_PROJECT_URL=	http://$(COMPONENT_NAME).sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
	sha256:b64790f94b926acd7e8f84c5d6000a86cb43967bd1e688b03089079799c9e889
COMPONENT_ARCHIVE_URL= \
	https://github.com/nigels-com/$(COMPONENT_NAME)/releases/download/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

CUSTOM.LDFLAGS.GL = -lGL
COMPONENT_PREP_ACTION = \
    ( cd "$(SOURCE_DIR)/config" && cp -pf "$(COMPONENT_DIR)/files/Makefile.illumos-gcc" ./ )

CFLAGS +=	-I$(SOURCE_DIR)/include
CFLAGS +=	-D_FILE_OFFSET_BITS=64

# These flags define the nuances of "oi-userland" in "glew"'s Makefile dialect.
# They are common for build and install actions, so we define them once in an
# extra variable, and re-use it below. Note we use "CUSTOM.*" flags defined in
# the custom Makefile.illumos-gcc to append common oi-userland flag values
# and not override the project's CFLAGS etc. in whole.

COMPONENT_COMMON_ARGS  =	SYSTEM=illumos-gcc
COMPONENT_COMMON_ARGS +=	GLEW_PREFIX="$(USRDIR)"
COMPONENT_COMMON_ARGS +=	GLEW_DEST="$(USRDIR)"
COMPONENT_COMMON_ARGS +=	LIBDIR="$(USRLIBDIR.$(BITS))"
COMPONENT_COMMON_ARGS +=	PKGDIR="$(PKG_CONFIG_DIR.$(BITS))"
COMPONENT_COMMON_ARGS +=	CC="$(CC)"
COMPONENT_COMMON_ARGS +=	CUSTOM.CFLAGS.EXTRA="$(CFLAGS)"
COMPONENT_COMMON_ARGS +=	LD="$(CC)"
COMPONENT_COMMON_ARGS +=	CUSTOM.LDFLAGS.EXTRA="$(LDFLAGS)"
COMPONENT_COMMON_ARGS +=	CUSTOM.LDFLAGS.SO="$(LDFLAGS)"
COMPONENT_COMMON_ARGS +=	CUSTOM.LDFLAGS.GL="$(CUSTOM.LDFLAGS.GL)"
COMPONENT_COMMON_ARGS +=	AR="$(AR)"
COMPONENT_COMMON_ARGS +=	CUSTOM.ARFLAGS.EXTRA="$(ARFLAGS)"

### In case of updates, review what the glew Makefile defines (and expects)
### these commands to be. In particular, their LN="ln -sf" now, and it matters.
COMPONENT_COMMON_ARGS +=	RM="$(RM)"
COMPONENT_COMMON_ARGS +=	LN="$(SYMLINK) -f"

COMPONENT_BUILD_ARGS  +=	$(COMPONENT_COMMON_ARGS)
COMPONENT_BUILD_TARGETS =	all
COMPONENT_INSTALL_ARGS +=	$(COMPONENT_COMMON_ARGS)
COMPONENT_INSTALL_TARGETS =	install.all

# Auto-generated dependencies
REQUIRED_PACKAGES += service/opengl/ogl-select
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
