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

COMPONENT_NAME= babl
COMPONENT_VERSION= 0.1.10
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= Babl is a dynamic, any to any, pixel format conversion library
COMPONENT_FMRI = image/library/babl
COMPONENT_CLASSIFICATION = System/Multimedia Libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:943fc36ceac7dd25bc928256bc7b535a42989c6b971578146869eee5fe5955f4
COMPONENT_ARCHIVE_URL= \
  http://ftp.gimp.org/pub/babl/0.1/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://gegl.org/babl/
COMPONENT_LICENSE = LGLPv3
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(@D)  && \
                                autoreconf -f -i)


CONFIGURE_OPTIONS+= --disable-mmx
CONFIGURE_OPTIONS+= --disable-sse

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# FAIL: models (1 of 13, is not symmetric)
test: $(TEST_32_and_64)
