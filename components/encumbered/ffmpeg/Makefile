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
PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ffmpeg
COMPONENT_VERSION= 3.2.14
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= A very fast video and audio converter
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:d918bf3cec12e865f03eaf01c9a4b4d49bbd311217cb56f02fa7de95730ee096
COMPONENT_ARCHIVE_URL= \
  http://www.ffmpeg.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.ffmpeg.org/
COMPONENT_LICENSE = GPLv2
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_FMRI = video/ffmpeg

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS.32 += -fno-rename-registers
CFLAGS.32 += -fomit-frame-pointer
CFLAGS.32 += -fno-PIC -UPIC 
CFLAGS.32 += -mpreferred-stack-boundary=4

CFLAGS += $(CFLAGS.$(BITS))
CFLAGS += -I/usr/X11/include
CFLAGS += $(CPP_LARGEFILES)

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
CONFIGURE_OPTIONS += --enable-libx265
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
# Incompatible with GPLv2
#CONFIGURE_OPTIONS += --enable-libopencore-amrnb
CONFIGURE_OPTIONS += --enable-libass
CONFIGURE_OPTIONS += --enable-openssl
CONFIGURE_OPTIONS += --enable-openal
CONFIGURE_OPTIONS += --enable-avresample
# Incompatible with GPLv2
#CONFIGURE_OPTIONS += --enable-libopencore-amrwb
CONFIGURE_OPTIONS += --enable-libschroedinger
CONFIGURE_OPTIONS += --enable-libopenjpeg
CONFIGURE_OPTIONS += --enable-librtmp
CONFIGURE_OPTIONS += --enable-vdpau
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Use binaries and libraries from $(PROTO_DIR) for tests
COMPONENT_TEST_ENV+= PATH=$(PROTO_DIR)/usr/bin:$(PATH)
COMPONENT_TEST_ENV+= LD_LIBRARY_PATH=$(PROTO_DIR)/usr/lib

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results.master

COMPONENT_TEST_TRANSFORMS+= '-n -e "/TEST/p" '

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test:	$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += audio/lame
REQUIRED_PACKAGES += codec/libtheora
REQUIRED_PACKAGES += codec/speex
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/audio/libgsm
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += library/graphics/libvdpau
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/video/libass
REQUIRED_PACKAGES += library/video/libschroedinger
REQUIRED_PACKAGES += library/video/libvpx
REQUIRED_PACKAGES += library/video/x264
REQUIRED_PACKAGES += library/video/x265
REQUIRED_PACKAGES += library/video/xvid
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += video/rtmpdump
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxv
