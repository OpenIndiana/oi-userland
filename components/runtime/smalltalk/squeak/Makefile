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
# Copyright 2020, 2021, 2022, 2023, 2024, 2025, 2026 David Stes
#


#
# Package Makefile for the "Classic VM" Squeak Smalltalk system
# See http://squeak.org and http://squeakvm.org
#
# squeak uses cmake and a custom configure script (not GNU autoconf)
# in order to build this package, "cmake" and "pkg-config" must be installed
#
# squeak was built both in 32-bit and 64-bit mode
# but since 2023 version 4.20.6 now only in 64 bit per OpenIndiana request
# OpenIndiana is dropping 32bit libraries so we can't build 32bit any longer
#
# the squeak driver script was/is checking the Smalltalk image (using ckformat),
# and depending on whether the image is 32bit or 64bit,
# it launches the squeak virtual machine 32bit or 64bit for the image
#
# we now (since 4.20.6) try to use the 64bit executable to launch 32bit images
# and for 64bit images simply fail (with an error message)
#
# for 32-bit : ckformat reports 6505
# 6505: a 32-bit V3 image with closure support and float words stored 
# in native platform order
#
# for 64-bit : ckformat reports 68000
# 68000: a 64-bit V3 image with no closure support and 
# no native platform float word order requirement
#
# note that since 4.20.6 the 64bit images (68000) are no longer working
# but this is not much of a problem due to the fact that all images are 6502
# or 6504 (32bit)
#
# squeak places its 64-bit shared object files in
# usr/lib/squeak/<version>-<svnversion>_64bit/  with a _64bit suffix
# which is unfortunately not conforming to the usr/lib/amd64 usage
# and it generates a hard error by pkglint "64-bit object in 32-bit path"
# so we deliver a patch and rename files
# in order to put the 64-bit objects in their usual usr/lib/amd64 location

USE_COMMON_TEST_MASTER=no

# there is support for OpenSSL 1.1 and 3.x in the squeak SSL module
# but the SUnit squeak images tests seem to be written for old ssl versions
# this can be set before including shared-macros.mk
USE_OPENSSL10=yes

# the goal is to use libjpeg8-turbo (or any other libjpeg implementation)
# special care for included header files as the struct sizes vary
# we 'fix' the Squeak source code that has an old libjpeg included in source
# this should be fixed upstream in the Squeak sources
# the default OpenIndiana JPEG_IMPLEM at time of writing is libjpeg8-turbo
JPEG_IMPLEM=libjpeg8-turbo

include ../../../../make-rules/shared-macros.mk

# the version is the same as the VMMaker Smalltalk sources
# it cannot be changed here randomly, it must match the VMMaker version

COMPONENT_NAME=		squeak
COMPONENT_VERSION=	4.21.3
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	The Squeak Virtual Machine
COMPONENT_PROJECT_URL=	http://www.squeak.org
COMPONENT_ARCHIVE_URL=  http://squeakvm.org
COMPONENT_FMRI=		runtime/smalltalk/squeak
COMPONENT_CLASSIFICATION=	Development/Smalltalk
# the svn repository has many files that we do not need
# and checking out everything often causes timeouts
# so only check out the following three subdirectories
SQREPO=                 http://squeakvm.org/svn/squeak/trunk
SVN_REPO_0=             $(SQREPO)/src
SVN_REPO_1=             $(SQREPO)/platforms/Cross
SVN_REPO_2=             $(SQREPO)/platforms/unix
COMPONENT_NAME_0=	$(COMPONENT_NAME)-src
COMPONENT_NAME_1=	$(COMPONENT_NAME)-platforms-Cross
COMPONENT_NAME_2=	$(COMPONENT_NAME)-platforms-unix
# also update squeak.ips when changing SQREV
SQREV=                  3840
SVN_REV_0=              $(SQREV)
SVN_REV_1=              $(SQREV)
SVN_REV_2=              $(SQREV)
# userland-fetch from archives
SVN_HASH_0=  sha256:afbfc87122465980c4857cb9f6c1ea1bf7b9fc25642ec3daefffd0472f889680
SVN_HASH_1=  sha256:dfa24407f16894d82ab527cce04a5e3b5cd108f8fe4d76aaf2027c60d1e37b44
SVN_HASH_2=  sha256:ddbf596e0b067848c3dd976d7a247bd8c6aa388c7e5e4decb81c8b8919e49938

# See http://wiki.squeak.org/squeak/933
# See http://wiki.squeak.org/squeak/159
# there's 2 license lines in the manifest, the MIT squeak.license and this one
COMPONENT_LICENSE=      Squeak4
COMPONENT_LICENSE_FILE= squeak4.license

# Squeak has an extensive test framework called SUnit
# it requires a X11 connection (graphical user interface)
# if connection to $DISPLAY fails from "gmake test" the tests will fail
# the tests are ran only on 32bit image for Squeak classical VM
# because inisqueak downloads a 32 bit image (provided by squeak.org)
# for OpenSmalltalk (see cog-spur and stack-spur) 32bit + 64bit
# since version 2023 4.20.6 we use a 64bit executable to run the 32image
# because OpenIndiana stopped shipping 32bit libraries for 32bit executables
COMPONENT_TEST_CMD=	$(COMPONENT_TEST_RESULTS_DIR)/testrunner.sh $(BITS) $(COMPONENT_DIR) $(BUILD_DIR_64)

include $(WS_MAKE_RULES)/common.mk

PKG_OPTIONS += -DBRANCHID="$(BRANCHID)"
PKG_OPTIONS += -DSVN_REV="$(SQREV)"

PATH=$(PATH.gnu)

# override gcc_OPT (defaults to -O3) for the moment
# squeak compiles with -O2 or -O3 but
# KernelTests-Chronology with gcc 7.5 version 4.16.7 or 4.19.*
# gcc -O : 438 pass tests
# gcc -O2 : 20 failures 1 errors  #testAsDelay error
# the system compiled with -O3 / -O2 is usable but has Chronology failures

# the example squeak Makefile specifies _FILE_OFFSET_BITS=64
# goal is large file support (as in man lfcompile)
# lfcompile - large file compilation environment for 32-bit applications

gcc_OPT=	-O

# for gcc 14.2 add -Wno-error options
gcc_OPT+=		-Wno-error=implicit-function-declaration
gcc_OPT+=		-Wno-error=incompatible-pointer-types
gcc_OPT+=		-Wno-error=return-mismatch
gcc_OPT+=		-Wno-error=int-to-pointer-cast
gcc_OPT+=		-Wno-error=int-conversion

# add -D_FILE_OFFSET_BITS=64 to CPPFLAGS but unlike OpenSmalltalk,
# must also add this to CFLAGS because Squeak configure is not using CPPFLAGS
# (see CFLAGS += CPPFLAGS below)
# since 2023 4.20.6 compile 64bit without largefiles flags to open 32bit images
# CPPFLAGS +=     $(CPP_LARGEFILES)

# use libjpeg8 turbo (see Illumos feature request #7391 for libjpeg8-turbo)
# use --link-shared-lib to avoid the Squeak copy of libjpeg
CPPFLAGS +=     $(JPEG_CPPFLAGS)
LDFLAGS  +=     $(JPEG_LDFLAGS)

# include "jpeglib.h" uses incorrect /usr/include/jpeglib.h unless CFLAGS set
# CPPFLAGS seems not respected by Squeak configure while CFLAGS is
CFLAGS   +=     $(CPPFLAGS)

# cleanup the plugin directory
SOURCE_JPEG = $(SOURCE_DIR_1)/plugins/JPEGReadWriter2Plugin

# squeak configure looks for .svn or svnversion file, but
# prep-svn.mk did a svn export and created an unversioned copy of the sources
# CMakeLists.txt defines cross as unix/../Cross so set a softlink
COMPONENT_PRE_CONFIGURE_ACTION = \
( echo $(SQREV) > $(SOURCE_DIR_2)/svnversion; \
  if [ ! -L Cross ]; then ln -s $(SOURCE_DIR_1) Cross;fi ; \
  find $(SOURCE_JPEG) -type f \
     \! -name JPEGReadWriter2Plugin.h \
     \! -name sqJPEGReadWriter2Plugin.c \
     \! -name Error.c \
     \! -name jinclude.h \
     \! -name jmemdatasrc.c \
     \! -name jmemdatadst.c \
  -exec rm {} \;)

# clean up symbolic link set in pre configure action
# also when we started to use 3 subversion packages, the .prep and .patched files started to appear in the component dir
CLEAN_PATHS+= Cross
CLEAN_PATHS+= .prep
CLEAN_PATHS+= .patched
CLEAN_PATHS+= .patched-02-openssl-cmake.patch
CLEAN_PATHS+= .patched-03-cameraconfig.patch
CLEAN_PATHS+= .patched-04-sqCamera.patch
CLEAN_PATHS+= .patched-05-jmemdatasrc.patch
CLEAN_PATHS+= .patched-06-jmemdatadst.patch
CLEAN_PATHS+= .patched-07-sqJPEGReadWriter2Plugin.patch
CLEAN_PATHS+= .patched-08-JPEGReadWriter2Plugin.patch

# do not build vm-sound-Sun as we only package vm-sound-pulse (bug #17109)
# do not build Mpeg3Plugin and RePlugin as it uses old copies of those libraries
# do not build GStreamerPlugin, it uses the GStreamer 0.10 and not GStreamer 1.0 (bug #17111)
 
CONFIGURE_SCRIPT= $(SOURCE_DIR_2)/cmake/configure
CONFIGURE_OPTIONS +=	--src=$(SOURCE_DIR_0)
CONFIGURE_OPTIONS +=    --link-shared-lib
CONFIGURE_OPTIONS +=    --without-vm-sound-Sun
CONFIGURE_OPTIONS +=    --without-RePlugin
CONFIGURE_OPTIONS +=    --without-Mpeg3Plugin
CONFIGURE_OPTIONS +=    --without-GStreamerPlugin
CONFIGURE_OPTIONS +=    --without-ScratchPlugin
# cmake 4.x requires this -D because the CMakeLists.txt indicates cmake 2.x MINVERSION
CONFIGURE_OPTIONS +=    -DCMAKE_POLICY_VERSION_MINIMUM=3.5

# in the 64bit case the vm is called squeakvm64 (not squeakvm)
# the plugin directory under usr/lib/squeak has a _64bit suffix
# CONFIGURE_OPTIONS.64+=	--image64
# CONFIGURE_OPTIONS.64+=	--vm-only
# since 2023 4.20.6 we try to avoid CMakeLists.txt SET (SQ_VI_BYTES_PER_WORD 8)
CONFIGURE_OPTIONS.64+=	-Dversionsuffix=_64bit
CONFIGURE_OPTIONS.64+=	-Dscriptsuffix=64

# Makefile install/strip doesn't work
# the squeakvm is called either squeakvm or squeakvm64 in different directories
COMPONENT_POST_INSTALL_ACTION = \
( find $(PROTOUSRLIBDIR)/squeak -name 'squeakvm*' -exec strip {} \; )

#
# target to update the manifests from sample-manifest
#

rebuild-manifests::
	cp manifests/squeak.p5m squeak.p5m
	cp manifests/squeak-vep.p5m squeak-vep.p5m
	cp manifests/squeak-ssl.p5m squeak-ssl.p5m
	cp manifests/squeak-display-X11.p5m squeak-display-X11.p5m
	cp manifests/squeak-nodisplay.p5m squeak-nodisplay.p5m
	cp manifests/sample-manifest.p5m sample-manifest.p5m
	tools/subversion.sh $(SQREV) <sample-manifest.p5m >sample.p5m
	tools/classify.pl <sample.p5m
	tools/amd64-p5m.sh
	rm -f sample-manifest.p5m sample.p5m

# disable pkglint until we find solution for 64bit object in 32-bit path error
PKGLINT= /bin/true

# OpenGL support for mesa and nvidia
# to force using the nvidia libGL.so.1 use
# svccfg -s svc:/application/opengl/ogl-select
# setprop options/vendor = astring: nvidia
# ogl-select has a dependency on x11/library/mesa
REQUIRED_PACKAGES += x11/library/mesa
REQUIRED_PACKAGES += system/library/dbus

# Auto-generated dependencies
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxrender
