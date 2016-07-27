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
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libwebp
COMPONENT_SUMMARY=	WebP image format library
COMPONENT_PROJECT_URL=	http://www.webmproject.org/
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	System/Multimedia Libraries
COMPONENT_FMRI=	library/$(COMPONENT_NAME)

# The current version
COMPONENT_VERSION_1=	0.5.1
COMPONENT_SRC_1=		$(COMPONENT_NAME)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= \
	sha256:d355b88f028ceb5322d158ac8a2bb55f8f6b3218883280e02790ae4ff2f1556c
COMPONENT_ARCHIVE_URL_1= \
	https://github.com/webmproject/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION_1).tar.gz

# Older version for legacy compatibility
COMPONENT_VERSION_2	= 0.4.0
COMPONENT_ARCHIVE_HASH_2= \
	sha256:65364123c4f2c7417cbf29634a9c40a4519f79c7ca24f517bc2a7dc030d6357d
COMPONENT_ARCHIVE_URL_2= \
	https://github.com/webmproject/$(COMPONENT_NAME)/archive/v$(COMPONENT_VERSION_2).tar.gz
COMPONENT_SRC_2=		$(COMPONENT_NAME)-$(COMPONENT_VERSION_2)
COMPONENT_ARCHIVE_2=	$(COMPONENT_SRC_2).tar.gz

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH.32=/usr/gnu/bin:/usr/bin
PATH.64=/usr/gnu/bin/$(MACH64):/usr/gnu/bin:/usr/bin/$(MACH64):/usr/bin
PATH=$(PATH.$(BITS))

CFLAGS +=	$(CPP_LARGEFILES)
CPPFLAGS +=	$(CPP_LARGEFILES)

# Common for both variants, as done below
COMPONENT_PREP_ACTION = \
    (cd $(SOURCE_DIR) && ./autogen.sh)

COMPONENT_PRE_CONFIGURE_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_ENV +=	CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS +=	--sysconfdir="$(ETCDIR)"
CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--enable-shared



# Unique stuff for the newer version
# Note: Old library was distributed without these
$(BUILD_DIR_32_1)/.configured:  CONFIGURE_OPTIONS+=	--enable-libwebpmux
$(BUILD_DIR_32_1)/.configured:  CONFIGURE_OPTIONS+=	--enable-libwebpdemux
$(BUILD_DIR_32_1)/.configured:  CONFIGURE_OPTIONS+=	--enable-libwebpdecoder
$(BUILD_DIR_32_1)/.configured:  CONFIGURE_OPTIONS+=	--enable-libwebpextras

$(BUILD_DIR_64_1)/.configured:  CONFIGURE_OPTIONS+=	--enable-libwebpmux
$(BUILD_DIR_64_1)/.configured:  CONFIGURE_OPTIONS+=	--enable-libwebpdemux
$(BUILD_DIR_64_1)/.configured:  CONFIGURE_OPTIONS+=	--enable-libwebpdecoder
$(BUILD_DIR_64_1)/.configured:  CONFIGURE_OPTIONS+=	--enable-libwebpextras

# Rename the include and pkgconfig files for their versions
# For includes it only suffices to do once, the 32-bit version
$(BUILD_DIR_32_1)/.installed:  COMPONENT_POST_INSTALL_ACTION=(\
    cd $(PROTOUSRINCDIR) && mv webp webp-$(COMPONENT_VERSION_1) && \
    cd $(PROTOUSRLIBDIR)/pkgconfig && mv libwebp.pc libwebp-$(COMPONENT_VERSION_1).pc )

$(BUILD_DIR_64_1)/.installed:  COMPONENT_POST_INSTALL_ACTION=(\
    cd $(PROTOUSRLIBDIR64)/pkgconfig && mv libwebp.pc libwebp-$(COMPONENT_VERSION_1).pc )



# Macros to configure, build, and install the old version for the time being.
# Rename the include and pkgconfig files for their versions
# For includes it only suffices to do once, the 32-bit version
$(BUILD_DIR_32_2)/.installed:  COMPONENT_POST_INSTALL_ACTION=(\
    cd $(PROTOUSRINCDIR) && mv webp webp-$(COMPONENT_VERSION_2) && \
    cd $(PROTOUSRLIBDIR)/pkgconfig && mv libwebp.pc libwebp-$(COMPONENT_VERSION_2).pc )

$(BUILD_DIR_64_2)/.installed:  COMPONENT_POST_INSTALL_ACTION=(\
    cd $(PROTOUSRLIBDIR64)/pkgconfig && mv libwebp.pc libwebp-$(COMPONENT_VERSION_2).pc )



# install the old version (_2) first
$(BUILD_DIR_32_1)/.installed:     $(BUILD_DIR_32_2)/.installed
$(BUILD_DIR_64_1)/.installed:     $(BUILD_DIR_64_2)/.installed

# common targets
build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

REQUIRED_PACKAGES += image/library/libjpeg6
REQUIRED_PACKAGES += image/library/libjpeg6-ijg
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/giflib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/freeglut
