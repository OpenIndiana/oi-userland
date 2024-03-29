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
# Copyright 2021,2022 Andreas Wacknitz
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= espeak
COMPONENT_VERSION= 1.48.4
HUMAN_VERSION= 1.48.04
COMPONENT_REVISION= 4
COMPONENT_SUMMARY= eSpeak - compact open source software speech synthesizer
COMPONENT_SRC= $(COMPONENT_NAME)-$(HUMAN_VERSION)-source
COMPONENT_ARCHIVE= $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= sha256:bf9a17673adffcc28ff7ea18764f06136547e97bbd9edf2ec612f09b207f0659
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/project/espeak/espeak/espeak-1.48/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://espeak.sourceforge.net/
COMPONENT_FMRI= library/speech/espeak
COMPONENT_CLASSIFICATION= Applications/Universal Access
COMPONENT_LICENSE= GPLv3

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CXXFLAGS += -fpermissive

BINDIR= /usr/bin/
LIBDIR= /usr/lib/$(MACH64)

COMPONENT_COMMON_ARGS += -C $(BUILD_DIR_$(BITS))/src
COMPONENT_COMMON_ARGS += EXTRA_LIBS=-lm 
COMPONENT_COMMON_ARGS += AUDIO=sada
COMPONENT_COMMON_ARGS += BINDIR=$(BINDIR)
COMPONENT_COMMON_ARGS += LIBDIR=$(LIBDIR)
COMPONENT_COMMON_ARGS += INSTALL=$(INSTALL)

COMPONENT_COMMON_ENV += CC=$(CC)
COMPONENT_COMMON_ENV += CXX=$(CXX)
COMPONENT_COMMON_ENV += CXXFLAGS="$(CXXFLAGS)"
COMPONENT_COMMON_ENV += LDFLAGS="$(LDFLAGS)"

COMPONENT_BUILD_ARGS += $(COMPONENT_COMMON_ARGS)
COMPONENT_BUILD_ENV += $(COMPONENT_COMMON_ENV)
COMPONENT_INSTALL_ARGS += $(COMPONENT_COMMON_ARGS)
COMPONENT_INSTALL_ENV += $(COMPONENT_COMMON_ENV)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
