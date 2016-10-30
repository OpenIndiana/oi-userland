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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ffmpeg
COMPONENT_VERSION= 2.8.6
COMPONENT_SUMMARY= A very fast video and audio converter
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:40611e329bc354592c6f8f1deb033c31b91f80e91f5707ca4f9afceca78d8e62
COMPONENT_ARCHIVE_URL= \
  http://www.ffmpeg.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.ffmpeg.org/
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = ffmpeg.license
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_FMRI = video/ffmpeg

include $(WS_TOP)/make-rules/encumbered.mk
include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/perl5/bin

CFLAGS.32 += -fno-rename-registers
CFLAGS.32 += -fomit-frame-pointer
CFLAGS.32 += -fno-PIC -UPIC
CFLAGS.32 += -mpreferred-stack-boundary=4

CFLAGS += $(CFLAGS.$(BITS))
CFLAGS += -I/usr/X11/include
CFLAGS += $(CPP_LARGEFILES)
CFLAGS += -DHAVE_OPENJPEG_2_0_OPENJPEG_H

CPPFLAGS += $($(COMPILER)_C99_ENABLE)

CONFIGURE_OPTIONS = --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --cc=$(CC)
CONFIGURE_OPTIONS += --enable-runtime-cpudetect
CONFIGURE_OPTIONS += --enable-mmx --enable-sse --enable-ssse3
CONFIGURE_OPTIONS += --disable-debug
CONFIGURE_OPTIONS += --enable-nonfree
CONFIGURE_OPTIONS += --enable-gpl
CONFIGURE_OPTIONS += --enable-postproc
CONFIGURE_OPTIONS += --enable-avfilter
CONFIGURE_OPTIONS += --enable-swscale
CONFIGURE_OPTIONS += --enable-libgsm
CONFIGURE_OPTIONS += --enable-libxvid
CONFIGURE_OPTIONS += --enable-libx264
# Don't enable it, resulting binary is not
# redistributable
#CONFIGURE_OPTIONS += --enable-libfaac
CONFIGURE_OPTIONS += --enable-libtheora
CONFIGURE_OPTIONS += --enable-libmp3lame
CONFIGURE_OPTIONS += --enable-libvorbis
CONFIGURE_OPTIONS += --enable-libvpx
CONFIGURE_OPTIONS += --enable-x11grab
CONFIGURE_OPTIONS += --enable-libspeex
CONFIGURE_OPTIONS += --enable-pthreads
# Incomaptible with GPLv2
#CONFIGURE_OPTIONS += --enable-libopencore-amrnb
CONFIGURE_OPTIONS += --enable-libass
CONFIGURE_OPTIONS += --enable-openssl
CONFIGURE_OPTIONS += --enable-openal
CONFIGURE_OPTIONS += --enable-avresample
# Incomaptible with GPLv2
#CONFIGURE_OPTIONS += --enable-libopencore-amrwb
CONFIGURE_OPTIONS += --enable-libschroedinger
CONFIGURE_OPTIONS += --enable-libopenjpeg
CONFIGURE_OPTIONS += --enable-librtmp
CONFIGURE_OPTIONS += --enable-vdpau
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)
