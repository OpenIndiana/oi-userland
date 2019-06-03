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
# Copyright 2017 Alexander Pyhalov
# Copyright 2019 Tim Mooney
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= gegl
COMPONENT_VERSION= 0.2.0
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= GEGL (Generic Graphics Library) is a graph based image processing framework
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:df2e6a0d9499afcbc4f9029c18d9d1e0dd5e8710a75e17c9b1d9a6480dd8d426
COMPONENT_ARCHIVE_URL= \
  http://ftp.gimp.org/pub/gegl/0.2/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.gegl.org/

GEGLDOCDIR = $(PROTO_DIR)/usr/share/doc/$(COMPONENT_NAME)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS += -std=gnu99
CFLAGS.32 = -D_FILE_OFFSET_BITS=64
CFLAGS += $(CFLAGS.$(BITS))

# build with the distribution default libjpeg
CFLAGS            +=    $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS          +=    $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS           +=    $(JPEG_LDFLAGS)

COMPONENT_PREP_ACTION += ( cd $(@D) && autoreconf -fi)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS+= --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS+= --datadir=$(USRSHAREDIR)
CONFIGURE_OPTIONS+= --infodir=$(USRSHAREDIR)/info
CONFIGURE_OPTIONS+= --without-libspiro
CONFIGURE_OPTIONS+= --without-libavformat
CONFIGURE_OPTIONS+= --without-libv4l
CONFIGURE_OPTIONS+= --enable-workshop
CONFIGURE_OPTIONS+= --enable-mmx=no
CONFIGURE_OPTIONS+= --enable-sse=no

CONFIGURE_ENV.64 += SDL_CONFIG=/usr/bin/$(MACH64)/sdl-config

COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR)  -p $(GEGLDOCDIR) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(CP)  $(COMPONENT_SRC)/{AUTHORS,README,ChangeLog,COPYING,NEWS,COPYING.LESSER} $(GEGLDOCDIR) ;

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/babl
REQUIRED_PACKAGES += image/library/$(JPEG_IMPLEM)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/sdl
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
