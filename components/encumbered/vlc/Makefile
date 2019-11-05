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
# Copyright 2015 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= vlc
COMPONENT_VERSION= 2.2.8
COMPONENT_REVISION= 1
COMPONENT_FMRI = media/vlc
COMPONENT_CLASSIFICATION = Applications/Sound and Video
COMPONENT_SUMMARY= Cross-platform media player and streaming server
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:9bf046848fb56d93518881b39099b8288ee005d5ba0ddf705b6f6643b8d562ec
COMPONENT_ARCHIVE_URL= \
  http://download.videolan.org/pub/videolan/vlc/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.videolan.org/vlc
COMPONENT_LICENSE = GPLv2.0,LGPLv2.1

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Required OpenGL extensions
CFLAGS+= -DGL_GLEXT_PROTOTYPES
# Define to ensure consistency
CFLAGS+= -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
CXXFLAGS+= -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64

# build with the distribution preferred libjpeg implementation
CFLAGS            +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS          +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS           +=    $(JPEG_LDFLAGS)

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static

# Input
CONFIGURE_OPTIONS += --enable-sout
CONFIGURE_OPTIONS += --enable-lua
CONFIGURE_OPTIONS += --enable-httpd
CONFIGURE_OPTIONS += --enable-vlm
CONFIGURE_OPTIONS += --enable-addonmanagermodules
CONFIGURE_OPTIONS += --disable-live555
CONFIGURE_OPTIONS += --disable-dc1394
CONFIGURE_OPTIONS += --disable-dv1394
CONFIGURE_OPTIONS += --disable-linsys
CONFIGURE_OPTIONS += --enable-dvdread
CONFIGURE_OPTIONS += --enable-dvdnav
CONFIGURE_OPTIONS += --enable-bluray
CONFIGURE_OPTIONS += --disable-opencv
CONFIGURE_OPTIONS += --disable-smbclient
CONFIGURE_OPTIONS += --enable-sftp
CONFIGURE_OPTIONS += --disable-v4l2
CONFIGURE_OPTIONS += --disable-decklink
CONFIGURE_OPTIONS += --enable-gnomevfs
CONFIGURE_OPTIONS += --disable-vcdx
CONFIGURE_OPTIONS += --disable-vcd
CONFIGURE_OPTIONS += --enable-libcddb
CONFIGURE_OPTIONS += --enable-screen
CONFIGURE_OPTIONS += --disable-vnc
CONFIGURE_OPTIONS += --disable-freerdp
CONFIGURE_OPTIONS += --disable-realrtsp

# Mux/Demux
CONFIGURE_OPTIONS += --enable-dvbpsi
CONFIGURE_OPTIONS += --disable-gme
CONFIGURE_OPTIONS += --disable-sid
CONFIGURE_OPTIONS += --enable-ogg
CONFIGURE_OPTIONS += --enable-mux_ogg
CONFIGURE_OPTIONS += --disable-shout
CONFIGURE_OPTIONS += --enable-mkv
CONFIGURE_OPTIONS += --disable-mod
CONFIGURE_OPTIONS += --enable-mpc

# Codec
CONFIGURE_OPTIONS += --disable-wma-fixed
CONFIGURE_OPTIONS += --disable-shine
CONFIGURE_OPTIONS += --disable-mmal-codec
CONFIGURE_OPTIONS += --disable-crystalhd
CONFIGURE_OPTIONS += --enable-mad
CONFIGURE_OPTIONS += --disable-merge-ffmpeg
CONFIGURE_OPTIONS += --disable-gst-decode
CONFIGURE_OPTIONS += --enable-avcodec
CONFIGURE_OPTIONS += --disable-libva
CONFIGURE_OPTIONS += --disable-dxva2
CONFIGURE_OPTIONS += --disable-vda
CONFIGURE_OPTIONS += --enable-avformat
CONFIGURE_OPTIONS += --enable-swscale
CONFIGURE_OPTIONS += --disable-postproc
CONFIGURE_OPTIONS += --enable-faad
CONFIGURE_OPTIONS += --enable-dxva2
CONFIGURE_OPTIONS += --enable-twolame
CONFIGURE_OPTIONS += --enable-dxva2
CONFIGURE_OPTIONS += --enable-dca
CONFIGURE_OPTIONS += --enable-flac
CONFIGURE_OPTIONS += --enable-libmpeg2
CONFIGURE_OPTIONS += --enable-vorbis
CONFIGURE_OPTIONS += --enable-speex
CONFIGURE_OPTIONS += --enable-opus
CONFIGURE_OPTIONS += --enable-theora
CONFIGURE_OPTIONS += --enable-schroedinger
CONFIGURE_OPTIONS += --enable-png
CONFIGURE_OPTIONS += --enable-jpeg
CONFIGURE_OPTIONS += --disable-x262
CONFIGURE_OPTIONS += --disable-x265
CONFIGURE_OPTIONS += --enable-x264
CONFIGURE_OPTIONS += --disable-mfx
CONFIGURE_OPTIONS += --disable-fluidsynth
CONFIGURE_OPTIONS += --disable-zvbi
CONFIGURE_OPTIONS += --enable-telx
CONFIGURE_OPTIONS += --enable-libass
CONFIGURE_OPTIONS += --disable-kate
CONFIGURE_OPTIONS += --disable-tiger

# Video
CONFIGURE_OPTIONS += --with-x
CONFIGURE_OPTIONS += --enable-xcb
CONFIGURE_OPTIONS += --enable-xvideo
CONFIGURE_OPTIONS += --enable-vdpau
CONFIGURE_OPTIONS += --enable-sdl
CONFIGURE_OPTIONS += --enable-sdl-image
CONFIGURE_OPTIONS += --enable-freetype
CONFIGURE_OPTIONS += --enable-fribidi
CONFIGURE_OPTIONS += --enable-fontconfig
CONFIGURE_OPTIONS += --enable-svg
CONFIGURE_OPTIONS += --enable-svgdec
CONFIGURE_OPTIONS += --disable-caca
CONFIGURE_OPTIONS += --disable-kva
CONFIGURE_OPTIONS += --disable-mmal-vout

# Audio
CONFIGURE_OPTIONS += --enable-pulse
CONFIGURE_OPTIONS += --disable-jack
CONFIGURE_OPTIONS += --enable-samplerate
CONFIGURE_OPTIONS += --disable-kai
CONFIGURE_OPTIONS += --disable-chromaprint

# Interface
CONFIGURE_OPTIONS += --enable-qt
CONFIGURE_OPTIONS += --enable-skins2
CONFIGURE_OPTIONS += --disable-libtar
CONFIGURE_OPTIONS += --disable-ncurses
CONFIGURE_OPTIONS += --disable-lirc

# Filters
CONFIGURE_OPTIONS += --disable-goom
CONFIGURE_OPTIONS += --disable-projectm
CONFIGURE_OPTIONS += --disable-vsxu
CONFIGURE_OPTIONS += --disable-atmo
CONFIGURE_OPTIONS += --enable-glspectrum

# Services
CONFIGURE_OPTIONS += --enable-bonjour
CONFIGURE_OPTIONS += --disable-udev
CONFIGURE_OPTIONS += --enable-mtp
CONFIGURE_OPTIONS += --enable-upnp

# Misc
CONFIGURE_OPTIONS += --enable-libxml2
CONFIGURE_OPTIONS += --disable-libgcrypt
CONFIGURE_OPTIONS += --disable-gnutls # Requested 'gnutls >= 3.0.20' but version of GnuTLS is 2.8.6
CONFIGURE_OPTIONS += --enable-taglib
CONFIGURE_OPTIONS += --enable-notify


build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += audio/faad2
REQUIRED_PACKAGES += audio/twolame
REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += codec/libtheora
REQUIRED_PACKAGES += codec/speex
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += image/library/sdl-image
REQUIRED_PACKAGES += library/audio/liba52
REQUIRED_PACKAGES += library/audio/libdca
REQUIRED_PACKAGES += library/audio/libmad
REQUIRED_PACKAGES += library/audio/libmpcdec
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/audio/taglib
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gnome/gnome-vfs
REQUIRED_PACKAGES += library/libebml
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += library/libmtp
REQUIRED_PACKAGES += library/libnotify
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libsamplerate
REQUIRED_PACKAGES += library/libssh2
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += library/qt4
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/speexdsp
REQUIRED_PACKAGES += library/video/libass
REQUIRED_PACKAGES += library/video/libbluray
REQUIRED_PACKAGES += library/video/libdvbpsi
REQUIRED_PACKAGES += library/video/libdvdnav
REQUIRED_PACKAGES += library/video/libdvdread
REQUIRED_PACKAGES += library/video/libmatroska
REQUIRED_PACKAGES += library/video/libmpeg2
REQUIRED_PACKAGES += library/video/libschroedinger
REQUIRED_PACKAGES += library/video/libvpx
REQUIRED_PACKAGES += library/video/x264
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/freetype-2
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/libupnp
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/network/avahi
REQUIRED_PACKAGES += video/ffmpeg
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxinerama
REQUIRED_PACKAGES += x11/library/libxpm
REQUIRED_PACKAGES += x11/library/xcb-util-keysyms
