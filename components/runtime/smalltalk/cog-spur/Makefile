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
# Copyright 2020, 2021, 2022, 2023, 2024 David Stes
#


#
# Package Makefile for the "OpenSmalltalk Cog Spur" Squeak Smalltalk system
# See http://squeak.org and http://opensmalltalk.org
#

# opensmalltalk-vm can be built both in 32 and 64bit
# since december 2023 version 5.0.3339 we only deliver ELF64 bit executables
# because the required 32bit libraries are no longer available
BUILD_BITS=64
USE_COMMON_TEST_MASTER= no

# the SSL module is supporting 1.1 and 3.x but SUnit testframework is not
USE_OPENSSL10=yes

# currently the JPEGReadWriter2Plugin is disabled in plugins.int
#
# the goal is to use libjpeg8-turbo (or any other libjpeg implementation)
# special care for included header files as the struct sizes vary
# we 'fix' the Squeak source code that has an old libjpeg included in source
# this should be fixed upstream in the Squeak sources
# the default OpenIndiana JPEG_IMPLEM at time of writing is libjpeg8-turbo
JPEG_IMPLEM=libjpeg8-turbo

include ../../../../make-rules/shared-macros.mk

# there is no official triplet version for opensmalltalk-vm
# we use 5.0.<n> for VMMaker.oscog-eem.<n> or VMMaker.oscog-mt.<n>
# sometimes the Stack VM is generated from a different VMMaker as the Cog VM

COMPONENT_NAME=		cog-spur
COMPONENT_VERSION=	5.0.3453
GIT_TAG=		sun-v5.0.66
PLUGIN_REV=		5.0-202409081304-cog
COMPONENT_SUMMARY=	The OpenSmalltalk Cog Spur Virtual Machine
COMPONENT_PROJECT_URL=	http://www.squeak.org
COMPONENT_FMRI=		runtime/smalltalk/cog-spur
COMPONENT_CLASSIFICATION=	Development/Smalltalk

# See http://wiki.squeak.org/squeak/933
# See http://wiki.squeak.org/squeak/159
# there's 2 license lines in the manifest, the MIT squeak.license and this one
COMPONENT_LICENSE=	Squeak5
COMPONENT_LICENSE_FILE=	squeak5.license

COMPONENT_SRC=		opensmalltalk-vm-$(GIT_TAG)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e1cf8dbd8f46ff455e9f7c216af249903b09eb2dc54faf5176fb743bb638ff60
COMPONENT_ARCHIVE_URL=	https://codeload.github.com/cstes/opensmalltalk-vm/tar.gz/$(GIT_TAG)

# run SUnit tests in the build directories on 32bit and 64bit Squeak images
# AllocationTest and BitmapStreamTests are currently skipped
# see comments in the Squeak.image on those tests
COMPONENT_TEST_CMD=	$(COMPONENT_TEST_RESULTS_DIR)/testrunner.sh $(BITS) $(COMPONENT_DIR) $(BUILD_DIR_$(BITS))

include $(WS_MAKE_RULES)/common.mk

# problem with OpenSmalltalk libtool and /bin/bash
# since upgrade from libtool VERSION="2.4.6 Debian-2.4.6-2"
# to VERSION="2.4.6 Debian-2.4.6-9"
CONFIG_SHELL= /bin/sh

PKG_OPTIONS += -D PLUGIN_REV="$(PLUGIN_REV)"
PKG_OPTIONS += -DBRANCHID="$(BRANCHID)"

PATH=$(PATH.gnu)

# cleanup the plugin directory
SOURCE_JPEG = $(SOURCE_DIR)/platforms/Cross/plugins/JPEGReadWriter2Plugin

# remove old libjpeg6 b2 sources from tree
# opensmalltalk configure script checks for plugins files in builddir
COMPONENT_PRE_CONFIGURE_ACTION = ( \
	$(MKDIR) $(BUILD_DIR_32); \
	cp plugins.ext plugins.int $(BUILD_DIR_32); \
	$(MKDIR) $(BUILD_DIR_64); \
	cp plugins.ext plugins.int $(BUILD_DIR_64); \
        find $(SOURCE_JPEG) \
     \! -name JPEGReadWriter2Plugin.h \
     \! -name sqJPEGReadWriter2Plugin.c \
     \! -name Error.c \
     \! -name jinclude.h \
     \! -name jmemdatasrc.c \
     \! -name jmemdatadst.c \
  -exec rm {} \; \
	)

# the Squeak configure script detects the lfcompile flags
# but unfortunately I think some files do not #include "config.h"
# we have to make sure largefile support is enabled in the 32bit case
CPPFLAGS += $(CPP_LARGEFILES)

# Spur memory management sometimes not compatible with traditional malloc
LIBS = "-lmapmalloc"

# the default CFLAGS.gcc will be -m64 -O3 but this does not work for us
# opensmalltalk code is not compatible with the gcc optimizer -O2 or higher
gcc_OPT=		-DAIO_DEBUG -DNDEBUG -DDEBUGVM=0 -DCOGMTVM=0

CONFIGURE_SCRIPT= $(SOURCE_DIR)/platforms/unix/config/configure
CONFIGURE_OPTIONS +=	--without-npsqueak
CONFIGURE_OPTIONS +=	--with-vmversion=5.0
CONFIGURE_OPTIONS +=	--disable-dynamicopenssl
CONFIGURE_OPTIONS +=	--without-libtls
CONFIGURE_OPTIONS.32 +=	--with-src=src/spur32.cog
CONFIGURE_OPTIONS.64 +=	--with-src=src/spur64.cog

# epoll(5) seems to work, so use epoll instead of select(3c)
CONFIGURE_ENV    +=     ax_cv_have_epoll=yes
CONFIGURE_ENV    +=     ax_cv_have_epoll_pwait=yes
CONFIGURE_ENV    +=     CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV    +=     LIBS="$(LIBS)"
CONFIGURE_ENV.32 +=	TARGET_ARCH="-m32"
CONFIGURE_ENV.64 +=	TARGET_ARCH="-m64"

# for pkgsend generate (sample-manifest)
# the actual manifest uses a mediator mediated hardlink for the squeak manpage
PKG_HARDLINKS    += usr/share/man/man1/squeak.1

# the opensmalltalk Makefile does not use DESTDIR
COMPONENT_INSTALL_ARGS=  	ROOT=$(PROTO_DIR)
COMPONENT_BUILD_TARGETS= 	getversion squeak plugins ckformat
COMPONENT_INSTALL_TARGETS= 	install-squeak install-doc install-plugins \
	install-ckformat

# Makefile has no strip target
COMPONENT_POST_INSTALL_ACTION = \
( find $(PROTOUSRLIBDIR) -name 'squeak' -type f -exec strip {} \; )

#
# target to update the manifests from sample-manifest
#

rebuild-manifests::
	cp manifests/cog-spur.p5m cog-spur.p5m
	cp manifests/cog-spur-vep.p5m cog-spur-vep.p5m
	cp manifests/cog-spur-ssl.p5m cog-spur-ssl.p5m
	cp manifests/cog-spur-display-X11.p5m cog-spur-display-X11.p5m
	cp manifests/cog-spur-nodisplay.p5m cog-spur-nodisplay.p5m
	cp manifests/sample-manifest.p5m sample-manifest.p5m
	tools/pluginrev.sh $(PLUGIN_REV) <sample-manifest.p5m >sample.p5m
	tools/classify.pl <sample.p5m
	rm -f sample-manifest.p5m sample.p5m

REQUIRED_PACKAGES += x11/library/mesa
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library/freetype-2

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
