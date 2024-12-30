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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2023 Friedrich Kink.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= opal
COMPONENT_VERSION= 3.16.2
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= OPAL - Open Phone Abstraction Library
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI= library/libopal
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:9225e881e7a450d39f739be7db97d0b1f845c754afdc2f26d8ebdbd5799dd3ed
COMPONENT_ARCHIVE_URL= \
  https://sourceforge.net/projects/opalvoip/files/V3.16%20Procyon/Stable%202/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= MPLv1.0 

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_BUILD_ARGS += VERBOSE=1

COMPONENT_PREP_ACTION=( cd $(@D)/plugins && aclocal && autoconf && \
	cd $(@D) && aclocal && autoconf )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =  ( CLONEY_MODE=copy $(CLONEY) $(SOURCE_DIR) $(@D) )

COMPONENT_POST_CONFIGURE_ACTION = ( \
        $(CP) $(@D)/src/rtp/libsrtp/Makefile $(SOURCE_DIR)/src/rtp/libsrtp; \
	echo "install: ;  @\$$(MAKE) --file=$(SOURCE_DIR)/Makefile \$$(MAKECMDGOALS)" >> $(@D)/Makefile )

CXXFLAGS += -I$(@D)/src/rtp/libsrtp/crypto/include -fpic
CFLAGS += -I$(@D)/src/rtp/libsrtp/include -I$(@D)/src/rtp/libsrtp/crypto/include -fpic

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-localsrtp
CONFIGURE_OPTIONS += --enable-localopenh264
CONFIGURE_OPTIONS += PKG_CONFIG_PATH=/usr/lib/$(MACH64)/pkgconfig
CONFIGURE_OPTIONS += SPEEXDSP_CFLAGS=-I/usr/include/speex

# opal comes with SILK SDK, which has own build system
COMPONENT_BUILD_ENV += SILK_CC="$(CC)"
COMPONENT_BUILD_ENV += SILK_CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += SILK_LDFLAGS="$(LDFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += codec/libtheora
REQUIRED_PACKAGES += codec/speex
REQUIRED_PACKAGES += library/desktop/ptlib
REQUIRED_PACKAGES += library/opus
REQUIRED_PACKAGES += library/spandsp
REQUIRED_PACKAGES += library/speexdsp
REQUIRED_PACKAGES += library/video/libvpx
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
