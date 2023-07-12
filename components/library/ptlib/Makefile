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
# Copyright 2016 Aurelien Larcher.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= ptlib
COMPONENT_VERSION= 2.10.11
COMPONENT_REVISION= 5
COMPONENT_SUMMARY= PTLib Class Library
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI=library/desktop/ptlib
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:3a17f01d66301663f76130b425d93c2730f2a33df666982165166ff4653dc2c9
COMPONENT_ARCHIVE_URL= \
  https://download.gnome.org/sources/ptlib/2.10/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= MPLv1.0

CONFIGURE_FIX_LIBTOOL_RPATH = no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION=( cd $(@D)/plugins && aclocal && autoconf &&\
		cd $(@D)&& aclocal && autoconf)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --enable-plugins
CONFIGURE_OPTIONS += --enable-resolver
CONFIGURE_OPTIONS += --enable-opal
CONFIGURE_OPTIONS += --disable-openssl
CONFIGURE_OPTIONS += --enable-sunaudio
CONFIGURE_OPTIONS += --enable-url
CONFIGURE_OPTIONS += --enable-http
CONFIGURE_OPTIONS += --enable-httpforms
CONFIGURE_OPTIONS += --enable-httpsvc
CONFIGURE_OPTIONS += --enable-v4l2
CONFIGURE_OPTIONS += --enable-lua

COMPONENT_POST_INSTALL_ACTION= \
            (cd $(PROTOUSRDIR) ;  \
             $(MV) include/ptbuildopts.h include/ptbuildopts-$(BITS).h )

ENV += -i

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

REQUIRED_PACKAGES += library/audio/pulseaudio
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
