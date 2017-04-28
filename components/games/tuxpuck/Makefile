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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= tuxpuck
COMPONENT_FMRI= games/$(COMPONENT_NAME)
COMPONENT_VERSION= 0.8.2
COMPONENT_SUMMARY= Shufflepuck Cafe Clone
COMPONENT_LICENSE= GPL
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:62d9604ed69c27b9ca2be1312bc705b36de8ed509c539c6d81193e7846272f18
COMPONENT_ARCHIVE_URL= \
  http://www.sourcefiles.org/Games/Sports/Miscellaneous/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.sourcefiles.org/Games/Sports/Miscellaneous/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

LDFLAGS.32 += `sdl-config --libs`
LDFLAGS.64 += `/usr/bin/$(MACH64)/sdl-config --libs`
COMPONENT_BUILD_ENV+= CC=$(CC)
COMPONENT_BUILD_ENV+= CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV+= LDFLAGS="$(LDFLAGS.$(BITS))"

BINDIR= usr/bin
COMPONENT_INSTALL_ARGS += DESTDIR=$(PROTO_DIR)
COMPONENT_INSTALL_ARGS.32 += BINDIR=$(BINDIR)
COMPONENT_INSTALL_ARGS.64 += BINDIR=$(BINDIR)/$(MACH64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

include $(WS_MAKE_RULES)/depend.mk

REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += library/libpng16
REQUIRED_PACKAGES += library/libvorbis
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/library
