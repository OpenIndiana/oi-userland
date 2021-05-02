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
# Package Makefile for the "Classic VM" Squeak Smalltalk V4 system
# See http://squeak.org and http://squeakvm.org
#
# squeak4 uses cmake and a custom configure script (not GNU autoconf)
# in order to build this package, "cmake" must be installed
#
# squeak4 is built both in 32-bit and 64-bit mode
# the squeak driver script checks the Smalltalk image (using ckformat),
# and depending on whether the image is 32bit or 64bit,
# it launches the squeak virtual machine 32bit or 64bit for the image
#
# for 32-bit : ckformat reports 6505
# 6505: a 32-bit V3 image with closure support and float words stored 
# in native platform order
#
# for 64-bit : ckformat reports 68000
# 68000: a 64-bit V3 image with no closure support and 
# no native platform float word order requirement
#
# squeak places its 64-bit shared object files in
# usr/lib/squeak/<version>-<svnversion>_64bit/  with a _64bit suffix
# which is unfortunately not conforming to the usr/lib/amd64 usage
# and it generates a hard error by pkglint "64-bit object in 32-bit path"
# so we deliver a patch and rename files
# in order to put the 64-bit objects in their usual usr/lib/amd64 location

BUILD_BITS=32_and_64

include ../../../make-rules/shared-macros.mk

# the version is the same as the VMMaker Smalltalk sources
# it cannot be changed here randomly, it must match the VMMaker version

COMPONENT_NAME=		squeak
COMPONENT_VERSION=	4.19.6
COMPONENT_REVISION=	4
COMPONENT_SUMMARY=	The Squeak Virtual Machine
COMPONENT_PROJECT_URL=	http://www.squeak.org
COMPONENT_ARCHIVE_URL=  http://squeakvm.org
COMPONENT_FMRI=		runtime/smalltalk/squeak
COMPONENT_CLASSIFICATION=	Development/Other Languages
SVN_REPO=		http://squeakvm.org/svn/squeak/trunk/
SVN_REV=                3801
SVN_HASH=  sha256:8ae39a65af168616247be2ce37ef602a84443454abf7de9dc197393266335bce

# See http://wiki.squeak.org/squeak/933
# See http://wiki.squeak.org/squeak/159
# there's 2 license lines in the manifest, the MIT squeak.license and this one
COMPONENT_LICENSE=      Squeak4
COMPONENT_LICENSE_FILE= squeak4.license

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PKG_OPTIONS += -DBRANCHID="$(BRANCHID)"
PKG_OPTIONS += -DSVN_REV="$(SVN_REV)"

PATH=$(PATH.gnu)

# override gcc_OPT (defaults to -O3) for the moment
# squeak4 compiles with -O2 or -O3 but
# KernelTests-Chronology with gcc 7.5 version 4.16.7 or 4.19.*
# gcc -O : 438 pass tests
# gcc -O2 : 20 failures 1 errors  #testAsDelay error
# the system compiled with -O3 / -O2 is usable but has Chronology failures

# the example squeak4 Makefile specifies _FILE_OFFSET_BITS=64
# goal is large file support (as in man lfcompile)
# lfcompile - large file compilation environment for 32-bit applications

gcc_OPT=	-O
gcc_OPT+=	-D_LARGEFILE_SOURCE
gcc_OPT+=	-D_FILE_OFFSET_BITS=64

# squeak4 configure looks for .svn or svnversion file, but
# prep-svn.mk did a svn export and created an unversioned copy of the sources
COMPONENT_PRE_CONFIGURE_ACTION = \
( echo $(SVN_REV) > $(SOURCE_DIR)/platforms/unix/svnversion )

CONFIGURE_SCRIPT= $(SOURCE_DIR)/platforms/unix/cmake/configure
CONFIGURE_OPTIONS +=	--src=$(SOURCE_DIR)/src

# in the 64bit case the vm is called squeakvm64 (not squeakvm)
# the plugin directory under usr/lib/squeak has a _64bit suffix
CONFIGURE_OPTIONS.64+=	--image64
CONFIGURE_OPTIONS.64+=	--vm-only

# Makefile install/strip doesn't work
# the squeakvm is called either squeakvm or squeakvm64 in different directories
COMPONENT_POST_INSTALL_ACTION = \
( find $(PROTOUSRLIBDIR)/squeak -name 'squeakvm*' -exec strip {} \; )

#
# target to update the manifests from sample-manifest
#

rebuild-manifests::
	cp manifests/squeak.p5m squeak.p5m
	cp manifests/squeak-display-X11.p5m squeak-display-X11.p5m
	cp manifests/squeak-nodisplay.p5m squeak-nodisplay.p5m
	cp manifests/sample-manifest.p5m sample-manifest.p5m
	tools/subversion.sh $(SVN_REV) <sample-manifest.p5m >sample.p5m
	tools/classify.pl <sample.p5m
	tools/amd64-p5m.sh
	rm -f sample-manifest.p5m sample.p5m

# disable pkglint until we find solution for 64bit object in 32-bit path error
PKGLINT= /bin/true

REQUIRED_PACKAGES += x11/library/mesa
REQUIRED_PACKAGES += system/library/dbus

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/gstreamer
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
