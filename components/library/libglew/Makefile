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

# NOTE: This project links with /usr/openwin/lib/libGL.so.1, which unrolls
# to /usr/lib/GL/libGL.so.1 which is a symlink to run-time (hardware-related?)
# mediator in the ../../../var/run/opengl/lib/libGL.so.1. So far so good...
# In my case (GZ on a VirtualBox host, even though it is dual-booted and runs
# OI/Hipster natively at the moment) this library symlink points back to
# /usr/lib/mesa/libGL.so.1 and this one object points to /usr/lib/VBoxOGL.so
# rather than the nearby mesa objects. This breaks the build because pkgmogrify
# insists on objects coming from known repo's, and because ultimate objects do
# refer to virtualbox rather than libs expected available on all deployments!
# Perhaps we should *require* do the builds in a dedicated local zone?..
# TODO: Find out the root-cause and attach a patch-file with a fix to this.

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		glew
COMPONENT_VERSION=	1.13.0
COMPONENT_SUMMARY=	The OpenGL Extension Wrangler Library
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_FMRI=		x11/library/lib$(COMPONENT_NAME)
COMPONENT_LICENSE=	GLEW,Mesa3D,Khronos
COMPONENT_LICENSE_FILE=	LICENSE.txt
COMPONENT_PROJECT_URL=	http://$(COMPONENT_NAME).sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
	sha256:aa25dc48ed84b0b64b8d41cdd42c8f40f149c37fa2ffa39cd97f42c78d128bc7
COMPONENT_ARCHIVE_URL= \
	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

PATH=/usr/gnu/bin:/usr/bin

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

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

LIBDIR.32=$(USRLIBDIR)
LIBDIR.64=$(USRLIBDIR64)

COMPONENT_COMMON_ARGS  =	SYSTEM=illumos-gcc
COMPONENT_COMMON_ARGS +=	BINDIR="$(USRBINDIR$(BITS))"
COMPONENT_COMMON_ARGS +=	LIBDIR="$(LIBDIR.$(BITS))"
COMPONENT_COMMON_ARGS +=	INCDIR="$(USRINCDIR)"
COMPONENT_COMMON_ARGS +=	DESTDIR="$(PROTO_DIR)"
COMPONENT_COMMON_ARGS +=	GLEW_PREFIX="$(USRDIR)"
COMPONENT_COMMON_ARGS +=	GLEW_DEST="$(USRDIR)"
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

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
