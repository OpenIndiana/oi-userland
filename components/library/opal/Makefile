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

COMPONENT_NAME= opal
COMPONENT_VERSION= 3.10.10
COMPONENT_REVISION= 2
COMPONENT_SUMMARY= OPAL - Open Phone Abstraction Library
COMPONENT_PROJECT_URL = http://www.gnome.org
COMPONENT_FMRI= library/libopal
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Libraries
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:f208985003461b2743575eccac13ad890b3e5baac35b68ddef17162460aff864
COMPONENT_ARCHIVE_URL= \
  https://download.gnome.org/sources/$(COMPONENT_NAME)/3.10/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= MPLv1.0 

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

OPAL_FFMPEG_PATCH =\
sed -e 's/CODEC_ID/AV_&/' \
    -e 's/PIX_FMT_/AV_&/' \
    -i plugins/video/H.263-1998/h263-1998.cxx \
       plugins/video/common/dyna.cxx          \
       plugins/video/H.264/h264-x264.cxx      \
       plugins/video/MPEG4-ffmpeg/mpeg4.cxx \
&& \
sed -e '/<< mime.PrintContents/ s/mime/(const std::string\&)&/' \
    -i src/im/msrp.cxx


COMPONENT_PREP_ACTION=( cd $(@D)/plugins && aclocal && autoconf &&\
		cd $(@D)&& aclocal && autoconf && $(OPAL_FFMPEG_PATCH) )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --disable-iax
CONFIGURE_OPTIONS += --enable-localgsm
CONFIGURE_OPTIONS += --disable-x264
CONFIGURE_OPTIONS += --disable-libavcodec

# opal comes with SILK SDK, which has own build system
COMPONENT_BUILD_ENV += SILK_CC="$(CC)"
COMPONENT_BUILD_ENV += SILK_CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += SILK_LDFLAGS="$(LDFLAGS)"

COMPONENT_POST_INSTALL_ACTION= \
            (cd $(PROTOUSRDIR) ;  \
             $(MV) include/opal/opal/buildopts.h include/opal/opal/buildopts-$(BITS).h )


build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += codec/libtheora
REQUIRED_PACKAGES += codec/speex
REQUIRED_PACKAGES += library/desktop/ptlib
REQUIRED_PACKAGES += library/speexdsp
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
