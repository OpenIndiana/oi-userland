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
# Copyright 2016 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           intel-gpu-tools
COMPONENT_VERSION=        1.16
COMPONENT_FMRI=           x11/diagnostics/intel-gpu-tools
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  Intel Graphics driver debug tools
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:c6be6d8311a939dd7ebb4639a2605bdbe711a4d3c77c8273a83f2050c2723ae1
COMPONENT_ARCHIVE_URL= \
  http://www.x.org/releases/individual/app/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.x.org/
COMPONENT_LICENSE=      MIT License
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# For Gen 4 code
CFLAGS+= -Wno-array-bounds
CFLAGS+= -Wl,-R/usr/lib/xorg/$(ARCHLIBSUBDIR)

COMPONENT_PREP_ACTION = ( cd $(@D); \
	for f in `ggrep -rlh '\-\-as-needed'| grep Makefile`; \
	do sed -i -e 's;\--as-needed;-z,ignore;' $$f; done; )

CONFIGURATION_ENV+= PYTHON="$(PYTHON.3.4.$(BITS))"

CONFIGURE_OPTIONS+= --libexecdir=$(USRLIBDIR.$(BITS))
CONFIGURE_OPTIONS+= --disable-nouveau
CONFIGURE_OPTIONS+= --without-libunwind
CONFIGURE_OPTIONS.32+= --disable-largefile

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)


REQUIRED_PACKAGES += diagnostic/scanpci
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libdrm
