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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= pulseaudio
COMPONENT_VERSION= 1.1
COMPONENT_SUMMARY= Sample Rate Converter for audio
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:9b480bbb8c33feffeca7343fe56bf972d47b988d5c6e20b28eb742186b0bfc47
COMPONENT_ARCHIVE_URL= \
  http://freedesktop.org/software/pulseaudio/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.freedesktop.org/wiki/Software/PulseAudio/
COMPONENT_LICENSE_FILE = pulseaudio.license
COMPONENT_LICENSE = LGPLv2.1,GPLv2,MIT,adrian-license,Sun Public Domain license
COMPONENT_FMRI = library/audio/pulseaudio
COMPONENT_CLASSIFICATION = System/Multimedia Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =	( cd $(@D) && autoreconf --force --install )

LDFLAGS += -lnsl -lsocket -lgobject-2.0

CPPFLAGS += -I/usr/include/gc

CONFIGURE_OPTIONS += --disable-samplerate
CONFIGURE_OPTIONS += --disable-bluez

CONFIGURE_ENV	+= CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV	+= PERL=$(PERL)
CONFIGURE_ENV	+= PYTHON=$(PYTHON)

COMPONENT_BUILD_ARGS += V=0

$(INSTALL_32):	$(INSTALL_64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)
