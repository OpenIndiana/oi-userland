#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=        libao
COMPONENT_VERSION=     1.2.0
COMPONENT_SUMMARY=     libao - cross-platform audio library
COMPONENT_PROJECT_URL= https://www.xiph.org/ao/
COMPONENT_FMRI=        library/audio/libao
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_SRC=         $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=     $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= \
  https://downloads.xiph.org/releases/ao/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:03ad231ad1f9d64b52474392d63c31197b0bc7bd416e58b1c10a329a5ed89caf
COMPONENT_LICENSE=     GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += system/library
