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
# Copyright 2017 Gary Mills
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= espeak
COMPONENT_VERSION= 1.48.04
IPS_COMPONENT_VERSION= 1.48.4
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= eSpeak - compact open source software speech synthesizer
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)-source
COMPONENT_ARCHIVE= $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:bf9a17673adffcc28ff7ea18764f06136547e97bbd9edf2ec612f09b207f0659
COMPONENT_ARCHIVE_URL= \
  http://downloads.sourceforge.net/project/espeak/espeak/espeak-1.48/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://espeak.sourceforge.net/
COMPONENT_FMRI = library/speech/espeak
COMPONENT_CLASSIFICATION = Applications/Universal Access
COMPONENT_LICENSE = GPLv3
COMPONENT_LICENSE_FILE = License.txt

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

CXXFLAGS += -fpermissive

BINDIR.32=/usr/bin
BINDIR.64=/usr/bin/$(MACH64)

LIBDIR.32=/usr/lib
LIBDIR.64=/usr/lib/$(MACH64)

COMPONENT_COMMON_ARGS += -C $(BUILD_DIR_$(BITS))/src
COMPONENT_COMMON_ARGS += EXTRA_LIBS=-lm 
COMPONENT_COMMON_ARGS += AUDIO=sada
COMPONENT_COMMON_ARGS += BINDIR=$(BINDIR.$(BITS))
COMPONENT_COMMON_ARGS += LIBDIR=$(LIBDIR.$(BITS))
COMPONENT_COMMON_ARGS += INSTALL=$(INSTALL)

COMPONENT_COMMON_ENV += CC=$(CC)
COMPONENT_COMMON_ENV += CXX=$(CXX)
COMPONENT_COMMON_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_COMMON_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ARGS += $(COMPONENT_COMMON_ARGS)
COMPONENT_BUILD_ENV += $(COMPONENT_COMMON_ENV)
COMPONENT_INSTALL_ARGS += $(COMPONENT_COMMON_ARGS)
COMPONENT_INSTALL_ENV += $(COMPONENT_COMMON_ENV)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
