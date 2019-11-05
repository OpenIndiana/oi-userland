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

COMPONENT_NAME= libvisual
COMPONENT_VERSION= 0.4.0
COMPONENT_SUMMARY= Libvisual provides a convenient API for writing visualization plugins
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:78f38d3ce857edde5482aa4415b504bbcd4d4a688fd4de09ec2131ad08174279
COMPONENT_ARCHIVE_URL= \
  http://downloads.sourceforge.net/libvisual/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://sourceforge.net/projects/libvisual/
COMPONENT_LICENSE_FILE = COPYING
COMPONENT_LICENSE = LGPLv2.1
COMPONENT_FMRI = library/desktop/libvisual
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# This is necessary fro mapfile to be found
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

LDFLAGS += -Wl,-Mmap.remove_all

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					libtoolize --copy --force &&\
					aclocal -I m4 &&\
					automake -c -f -a &&\
					autoconf )


CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-shared=yes
CONFIGURE_OPTIONS += --enable-static=no

COMPONENT_POST_INSTALL_ACTION= \
            (cd $(PROTOUSRDIR) ;  \
             $(MV) include/libvisual-0.4/libvisual/lvconfig.h include/libvisual-0.4/libvisual/lvconfig-$(BITS).h ) 

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += library/glib2

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
