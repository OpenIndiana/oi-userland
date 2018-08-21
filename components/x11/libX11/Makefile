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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libX11

COMPONENT_VERSION= 1.6.6
COMPONENT_SUMMARY= libX11 - X11 core protocol client library
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:65fe181d40ec77f45417710c6a67431814ab252d21c2e85c75dd1ed568af414f
COMPONENT_ARCHIVE_URL= \
  https://xorg.freedesktop.org/archive/individual/lib/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = https://xorg.freedesktop.org
COMPONENT_FMRI = x11/library/libx11
COMPONENT_CLASSIFICATION = System/X11
COMPONENT_LICENSE = MIT
COMPONENT_LICENSE_FILE = COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CPPFLAGS += -I/usr/include/freetype2  -I/usr/include/X11  -I/usr/include/xcb  -DSUNSOFT -DMOTIFBC -DSUNSOFT_KBD

COMPONENT_PREP_ACTION =        ( cp -r $(COMPONENT_DIR)/srcs/* $(SOURCE_DIR) && \
					cd $(@D) &&  libtoolize --copy --force &&\
                                        aclocal -I m4 &&\
                                        automake -c -f -a &&\
                                        autoconf )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

LOCALE_LIB_DIR.32=/usr/lib/X11/locale
LOCALE_LIB_DIR.64=/usr/lib/X11/locale/$(MACH64)

CONFIGURE_ENV += LIB_MAN_SUFFIX=3x11
CONFIGURE_ENV += XLOCALEDIR="/usr/share/X11/locale:/usr/X11/share/X11/locale"
CONFIGURE_ENV += XLOCALELIBDIR="$(LOCALE_LIB_DIR.$(BITS))"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS +=  --without-xmlto 
CONFIGURE_OPTIONS +=  --without-fop
CONFIGURE_OPTIONS +=  --localstatedir=/var
CONFIGURE_OPTIONS +=  --enable-shared=yes
CONFIGURE_OPTIONS +=  --enable-static=no
CONFIGURE_OPTIONS +=  --without-lint
CONFIGURE_OPTIONS +=  --disable-lint-library
CONFIGURE_OPTIONS +=  --with-pic
CONFIGURE_OPTIONS +=  --enable-xthreads 
CONFIGURE_OPTIONS +=  --enable-loadable-i18n 
CONFIGURE_OPTIONS +=  --enable-xf86bigfont
CONFIGURE_OPTIONS +=  --enable-loadable-xcursor 
CONFIGURE_OPTIONS +=  --enable-xcms
CONFIGURE_OPTIONS +=  --enable-xlocaledir 
CONFIGURE_OPTIONS +=  --enable-xkb  
CONFIGURE_OPTIONS +=  --with-locale-lib-dir="$(LOCALE_LIB_DIR.$(BITS))"

COMPONENT_BUILD_ARGS.64=ADD_libX11_LDFLAGS="-Wl,-M$(COMPONENT_DIR)/mapfile-vers-64"
COMPONENT_BUILD_ARGS += $(COMPONENT_BUILD_ARGS.$(BITS))

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += x11/header/xf86bigfontproto

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libxau
REQUIRED_PACKAGES += x11/library/libxcb
REQUIRED_PACKAGES += x11/library/libxext
