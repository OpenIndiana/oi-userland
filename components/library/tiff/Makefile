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

COMPONENT_NAME= tiff
COMPONENT_VERSION= 4.0.6
COMPONENT_REVISION= 1
COMPONENT_SUMMARY= libtiff - library for reading and writing TIFF
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:4d57a50907b510e3049a4bba0d7888930fdfc16ce49f1bf693e5b6247370d68c
COMPONENT_ARCHIVE_URL= \
  http://download.osgeo.org/libtiff/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.remotesensing.org/libtiff/
COMPONENT_LICENSE_FILE = COPYRIGHT
COMPONENT_LICENSE = BSD-like
COMPONENT_FMRI = image/library/libtiff
COMPONENT_CLASSIFICATION = System/Multimedia Libraries

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --disable-cxx

COMPONENT_POST_INSTALL_ACTION= \
            (cd $(PROTOUSRDIR) ;  \
             $(MV) include/tiffconf.h include/tiffconf-$(BITS).h)


build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)
