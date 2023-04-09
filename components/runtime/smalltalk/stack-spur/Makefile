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
# Copyright 2020, 2021, 2022, 2023 David Stes
#


#
# Package Makefile for the "OpenSmalltalk" Squeak Smalltalk system
# See http://squeak.org and http://opensmalltalk.org
#

# opensmalltalk-vm can be built both in 32 and 64bit
#
# we deliver our own script squeak.ips as driver script
#
# the driver script checks (with ckformat) the Smalltalk image
# image format 6521 or 7033 : start VM 32bit 
# image format 68021 or 68533 : start VM 64bit
BUILD_BITS=32_and_64
USE_COMMON_TEST_MASTER= no

include ../../../../make-rules/shared-macros.mk

# there is no official triplet version for opensmalltalk-vm
# we use 5.0.<n> for VMMaker.oscog-eem.<n>
# sometimes the Stack VM is generated from a different VMMaker as the Cog VM

COMPONENT_NAME=		stack-spur
COMPONENT_VERSION=	5.0.3307
COMPONENT_REVISION=	1
GIT_TAG=		sun-v5.0.59
PLUGIN_REV=		5.0-202304081342
COMPONENT_SUMMARY=	The OpenSmalltalk Stack Spur Virtual Machine
COMPONENT_PROJECT_URL=	http://www.squeak.org
COMPONENT_FMRI=		runtime/smalltalk/stack-spur
COMPONENT_CLASSIFICATION=	Development/Smalltalk

# See http://wiki.squeak.org/squeak/933
# See http://wiki.squeak.org/squeak/159
# there's 2 license lines in the manifest, the MIT squeak.license and this one
COMPONENT_LICENSE=	Squeak5
COMPONENT_LICENSE_FILE=	squeak5.license

COMPONENT_SRC=		opensmalltalk-vm-$(GIT_TAG)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:68b6ca9dbd03f4a738ec75203e3ffb1df36e87ce9fd9ab3f1df2fa5842615bc4
COMPONENT_ARCHIVE_URL=	https://codeload.github.com/cstes/opensmalltalk-vm/tar.gz/$(GIT_TAG)

# run SUnit tests in the build directories on 32bit and 64bit Squeak images
# currently two tests are skipped : AllocationTest and BitmapStreamTests
# see comments on those classes in the Squeak image itself for more info
COMPONENT_TEST_CMD=	$(COMPONENT_TEST_RESULTS_DIR)/testrunner.sh $(BITS) $(COMPONENT_DIR) $(BUILD_DIR_$(BITS))

include $(WS_MAKE_RULES)/common.mk

# problem with OpenSmalltalk libtool and /bin/bash
# since upgrade from libtool VERSION="2.4.6 Debian-2.4.6-2"
# to VERSION="2.4.6 Debian-2.4.6-9"
CONFIG_SHELL= /bin/sh

PKG_OPTIONS += -D PLUGIN_REV="$(PLUGIN_REV)"
PKG_OPTIONS += -DBRANCHID="$(BRANCHID)"

PATH=$(PATH.gnu)

# opensmalltalk configure script checks for plugins files in builddir
COMPONENT_PRE_CONFIGURE_ACTION = ( \
	$(MKDIR) $(BUILD_DIR_32); \
	cp plugins.ext plugins.int $(BUILD_DIR_32); \
	$(MKDIR) $(BUILD_DIR_64); \
	cp plugins.ext plugins.int $(BUILD_DIR_64) \
	)

# the Squeak configure script detects the lfcompile flags
# but unfortunately I think some files do not #include "config.h"
# we have to make sure largefile support is enabled in the 32bit case
CPPFLAGS += $(CPP_LARGEFILES)

# Spur memory management sometimes not compatible with traditional malloc
LIBS = "-lmapmalloc"

# the default CFLAGS.gcc will be -m64 -O3 but this does not work for us
# opensmalltalk code is not compatible with the gcc optimizer -O2 or higher
gcc_OPT=		-DAIO_DEBUG -DNDEBUG -DDEBUGVM=0

CONFIGURE_SCRIPT= $(SOURCE_DIR)/platforms/unix/config/configure
CONFIGURE_OPTIONS +=	--with-vmversion=5.0
CONFIGURE_OPTIONS +=	--disable-dynamicopenssl
CONFIGURE_OPTIONS +=	--without-libtls
CONFIGURE_OPTIONS.32 +=	--with-src=src/spur32.stack
CONFIGURE_OPTIONS.64 +=	--with-src=src/spur64.stack
CONFIGURE_OPTIONS +=	--disable-cogit
CONFIGURE_OPTIONS +=	--without-vm-display-fbdev
CONFIGURE_OPTIONS +=	--without-npsqueak

# epoll(5) seems to work, so use epoll instead of select(3c)
CONFIGURE_ENV    +=     ax_cv_have_epoll=yes
CONFIGURE_ENV    +=     ax_cv_have_epoll_pwait=yes
CONFIGURE_ENV    +=     CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV    +=     LIBS="$(LIBS)"
CONFIGURE_ENV.32 +=	TARGET_ARCH="-m32"
CONFIGURE_ENV.64 +=	TARGET_ARCH="-m64"

# the opensmalltalk Makefile does not use DESTDIR
COMPONENT_INSTALL_ARGS=  	ROOT=$(PROTO_DIR)
COMPONENT_BUILD_TARGETS=        getversion squeak plugins ckformat
COMPONENT_INSTALL_TARGETS=      install-squeak install-doc install-plugins \
	install-ckformat

# Makefile has no strip target
COMPONENT_POST_INSTALL_ACTION = \
( find $(PROTOUSRLIBDIR) -name 'squeak' -type f -exec strip {} \; )

#
# target to update the manifests from sample-manifest
#

rebuild-manifests::
	cp manifests/stack-spur.p5m stack-spur.p5m
	cp manifests/stack-spur-ssl.p5m stack-spur-ssl.p5m
	cp manifests/stack-spur-vep.p5m stack-spur-vep.p5m
	cp manifests/stack-spur-display-X11.p5m stack-spur-display-X11.p5m
	cp manifests/stack-spur-nodisplay.p5m stack-spur-nodisplay.p5m
	cp manifests/sample-manifest.p5m sample-manifest.p5m
	tools/pluginrev.sh $(PLUGIN_REV) <sample-manifest.p5m >sample.p5m
	tools/classify.pl <sample.p5m
	rm -f sample-manifest.p5m sample.p5m

REQUIRED_PACKAGES += x11/library/mesa
REQUIRED_PACKAGES += system/library/dbus
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += x11/library/libxevie

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
