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
# Copyright 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= audacity
COMPONENT_VERSION= 2.1.1
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= Cross-platform audio software for recording and editing
COMPONENT_SRC= audacity-Audacity-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= Audacity-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:1ec4c3b92e3653a83b30b37f67d1778050eb87bd651266865a1e30fe1f402892
COMPONENT_ARCHIVE_URL= \
  https://github.com/audacity/audacity/archive/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.audacityteam.org/
COMPONENT_FMRI= audio/audacity
COMPONENT_CLASSIFICATION= Applications/Sound and Video
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= LICENSE.txt

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =        (cd $(@D) && autoreconf -fi)

CFLAGS += -std=c99 $(CPP_XPG6MODE)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CP) -rpP $(SOURCE_DIR)/* $(@D))
CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib
CONFIGURE_OPTIONS+= --enable-unicode
CONFIGURE_OPTIONS+= --with-lib-preference="local"
CONFIGURE_OPTIONS+= --with-expat=system
CONFIGURE_OPTIONS+= --with-libsndfile=system
CONFIGURE_OPTIONS+= --with-libsoxr=system
CONFIGURE_OPTIONS+= --with-midi
CONFIGURE_OPTIONS+= --with-portaudio
CONFIGURE_OPTIONS+= --disable-alsa
CONFIGURE_OPTIONS+= --with-widgetextra
CONFIGURE_OPTIONS+= --with-ffmpeg=system
CONFIGURE_OPTIONS+= --with-libflac=system
CONFIGURE_OPTIONS+= --with-libid3tag=system
CONFIGURE_OPTIONS+= --with-libmad=system
CONFIGURE_OPTIONS+= --with-lame=system
CONFIGURE_OPTIONS+= --with-libtwolame=system
CONFIGURE_OPTIONS+= --with-libvorbis=system
CONFIGURE_OPTIONS+= --with-portmixer=yes

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES += shell/which
REQUIRED_PACKAGES += video/ffmpeg

REQUIRED_PACKAGES += audio/twolame
REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += library/audio/libid3tag
REQUIRED_PACKAGES += library/audio/libmad
REQUIRED_PACKAGES += library/audio/soxr
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/graphics/wxwidgets
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
