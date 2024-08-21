
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
# Copyright 2023 Niklas Poslovski
#

USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ffmpeg
COMPONENT_VERSION=	6.1.2
COMPONENT_SUMMARY=	A very fast video and audio converter (runtime libraries)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:3b624649725ecdc565c903ca6643d41f33bd49239922e45c9b1442c63dca4e38
COMPONENT_PROJECT_URL=  https://www.ffmpeg.org
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/ffmpeg-6
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE=      LGPLv2.1+, GPLv2, MIT/X11/BSD-style

COMPONENT_FMRI.developer =	developer/ffmpeg-6
COMPONENT_SUMMARY.developer =	$(COMPONENT_SUMMARY) (development files)

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

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
# force additional new CPU instruction enablement
CONFIGURE_OPTIONS += --enable-avx
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
CONFIGURE_OPTIONS += --enable-libdav1d
CONFIGURE_OPTIONS += --enable-libwebp
# Don't enable it, resulting binary is not 
# redistributable
#CONFIGURE_OPTIONS += --enable-libfaac
CONFIGURE_OPTIONS += --enable-libtheora
CONFIGURE_OPTIONS += --enable-libmp3lame
CONFIGURE_OPTIONS += --enable-libvorbis
CONFIGURE_OPTIONS += --enable-libvpx
# x11grab has been replaced by the x11xcb options
#CONFIGURE_OPTIONS += --enable-x11grab
CONFIGURE_OPTIONS += --enable-libxcb
CONFIGURE_OPTIONS += --enable-libspeex
CONFIGURE_OPTIONS += --enable-pthreads
# Incompatible with GPLv2
#CONFIGURE_OPTIONS += --enable-libopencore-amrnb
CONFIGURE_OPTIONS += --enable-libass
CONFIGURE_OPTIONS += --enable-openssl
CONFIGURE_OPTIONS += --enable-openal
# don't enable avresample any more, it's long-deprecated.  Use swresample
# instead
#CONFIGURE_OPTIONS += --enable-avresample
CONFIGURE_OPTIONS += --enable-swresample
# Incompatible with GPLv2
#CONFIGURE_OPTIONS += --enable-libopencore-amrwb
# libschroedinger support was removed in 3.4.x
#CONFIGURE_OPTIONS += --enable-libschroedinger
CONFIGURE_OPTIONS += --enable-libopenjpeg
CONFIGURE_OPTIONS += --enable-librtmp
CONFIGURE_OPTIONS += --enable-vdpau
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
# these tests cause problems, skip them
CONFIGURE_OPTIONS += --ignore-tests=source

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# We do not need documentation for old ffmpeg version
CONFIGURE_OPTIONS += --disable-doc
# Install ffmpeg-6 development support into dedicated directories
CONFIGURE_OPTIONS += --incdir=$(CONFIGURE_PREFIX)/include/ffmpeg-6
CONFIGURE_OPTIONS += --pkgconfigdir=$(PKG_CONFIG_PATH.$(BITS))/ffmpeg-6
# We do not need programs in /usr/bin.  We cannot use --disable-programs
# configure option because testing needs the ffmpeg binary.
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRBINDIR) ;
# We do not need examples and other share files needed for programs
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRSHAREDIR)/ffmpeg ;

COMPONENT_TEST_ENV += PATH=$(PROTO_DIR)/$(CONFIGURE_BINDIR.$(BITS)):$(PATH)
COMPONENT_TEST_ENV += LD_LIBRARY_PATH=$(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS))

COMPONENT_TEST_TRANSFORMS+= '-n -e "/TEST/p" -e "/^IGNORE/p" '

# You must run the 'install' target before running the test
# suite, as we use binaries and libraries from $(PROTO_DIR) for tests
# to reduce issues with all the test binaries not being able to find
# ffmpeg's libraries.
test:	install $(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += audio/lame
REQUIRED_PACKAGES += codec/dav1d
REQUIRED_PACKAGES += codec/libtheora
REQUIRED_PACKAGES += codec/speex
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += image/library/openjpeg
REQUIRED_PACKAGES += library/audio/libgsm
REQUIRED_PACKAGES += library/audio/openal
REQUIRED_PACKAGES += library/graphics/libvdpau
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/libwebp
REQUIRED_PACKAGES += library/sdl2
REQUIRED_PACKAGES += library/video/libass
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
