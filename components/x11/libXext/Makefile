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

COMPONENT_NAME= libXext
COMPONENT_VERSION= 1.3.3
COMPONENT_SUMMARY= libXext - X11 protocol common extensions client library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:b518d4d332231f313371fdefac59e3776f4f0823bcb23cf7c7305bfb57b16e35
COMPONENT_ARCHIVE_URL= \
  http://xorg.freedesktop.org/archive/individual/lib/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://xorg.freedesktop.org
COMPONENT_FMRI = x11/library/libxext
COMPONENT_CLASSIFICATION = System/X11
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

CPPFLAGS += -DSUNSOFT

LD_OPTIONS += -M $(COMPONENT_DIR)/mapfile-vers

COMPONENT_PREP_ACTION =        ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR) && \
					cd $(@D) &&  libtoolize --copy --force &&\
                                        aclocal -I . &&\
                                        automake -c -f -a &&\
                                        autoconf )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV += LIB_MAN_SUFFIX=3xext
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxevie
REQUIRED_PACKAGES += x11/library/libxscrnsaver
