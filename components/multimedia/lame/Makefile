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

COMPONENT_NAME= lame
COMPONENT_VERSION= 3.99.5
COMPONENT_REVISION= 3
COMPONENT_SUMMARY= lame  MP3 encoder
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:24346b4158e4af3bd9f2e194bb23eb473c75fb7377011523353196b19b9a23ff
COMPONENT_ARCHIVE_URL= \
  http://tenet.dl.sourceforge.net/project/lame/lame/3.99/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://lame.sourceforge.net/
COMPONENT_LICENSE = LGPLv2
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_CLASSIFICATION = System/Media
COMPONENT_FMRI = audio/lame

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --with-fileio=sndfile
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-rpath

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libsndfile
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
