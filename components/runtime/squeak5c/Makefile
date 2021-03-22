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
# Copyright 2020, 2021 David Stes
#


#
# Package Makefile for the "OpenSmalltalk Cog Spur" Squeak Smalltalk V5 system
# See http://squeak.org and http://opensmalltalk.org
#

# opensmalltalk-vm can be built both in 32 and 64bit
BUILD_BITS=32_and_64
USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

# there is no official triplet version for opensmalltalk-vm
# we use 5.0.<n> for VMMaker.oscog-eem.<n>
# sometimes the Stack VM is generated from a different VMMaker as the Cog VM

COMPONENT_NAME=		squeak-5c
COMPONENT_VERSION=	5.0.2945
COMPONENT_REVISION=	2
GIT_TAG=		sun-v5.0.26
PLUGIN_REV=		5.0-202102111620-cog
COMPONENT_SUMMARY=	The Cog Implementation of the Squeak V5 Smalltalk Virtual Machine
COMPONENT_PROJECT_URL=	http://www.squeak.org
COMPONENT_FMRI=		runtime/squeak-5c
COMPONENT_CLASSIFICATION=	Development/Other Languages

# See http://wiki.squeak.org/squeak/933
# See http://wiki.squeak.org/squeak/159
# there's 2 license lines in the manifest, the MIT squeak.license and this one
COMPONENT_LICENSE=	Squeak5
COMPONENT_LICENSE_FILE=	squeak5.license

COMPONENT_SRC=		opensmalltalk-vm-$(GIT_TAG)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:470a55c51da928bce248a6c1c239fa5c74cb5141b9a06119640c75602bbcf163
COMPONENT_ARCHIVE_URL=	https://codeload.github.com/cstes/opensmalltalk-vm/tar.gz/$(GIT_TAG)

TEST_TARGET= $(NO_TESTS)

# some builds seem to be broken with -Bdirect
# but issue is not reproducable
# LD_B_DIRECT=

# try to install the 32bit version before the 64bit version
build : $(BUILD_32) $(INSTALL_32) $(BUILD_64)

install : $(INSTALL_64)

include $(WS_MAKE_RULES)/common.mk

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

# the default CFLAGS.gcc will be -m64 -O3 but this does not work for us
# opensmalltalk code is not compatible with the gcc optimizer -O2 or higher
# also the -g (debug) flag is intentional, perhaps omit-frame-pointer issues
gcc_OPT=		-g -DAIO_DEBUG -DNDEBUG -DDEBUGVM=0 -DCOGMTVM=0

CONFIGURE_SCRIPT= $(SOURCE_DIR)/platforms/unix/config/configure
CONFIGURE_OPTIONS +=	--without-npsqueak
CONFIGURE_OPTIONS +=	--with-vmversion=5.0
CONFIGURE_OPTIONS +=	--disable-dynamicopenssl
CONFIGURE_OPTIONS +=	--without-libtls
CONFIGURE_OPTIONS.64 +=	--with-src=spur64src
CONFIGURE_OPTIONS.32 +=	--with-src=spursrc

CONFIGURE_ENV    +=     CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV.32 +=	TARGET_ARCH="-m32"
CONFIGURE_ENV.64 +=	TARGET_ARCH="-m64"

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
	cp manifests/squeak-5c.p5m squeak-5c.p5m
	cp manifests/squeak-5c-display-X11.p5m squeak-5c-display-X11.p5m
	cp manifests/squeak-5c-nodisplay.p5m squeak-5c-nodisplay.p5m
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
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/security/openssl-11
#REQUIRED_PACKAGES += runtime/squeak-5c-display-X11
#REQUIRED_PACKAGES += runtime/squeak-5c-nodisplay
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
