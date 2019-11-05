#
#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018, Michal Nowak
#

PREFERRED_BITS= 64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ghostscript
COMPONENT_VERSION=      9.26
COMPONENT_SUMMARY=	GPL Ghostscript
COMPONENT_PROJECT_URL=	https://ghostscript.com
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:831fc019bd477f7cc2d481dc5395ebfa4a593a95eb2fe1eb231a97e450d7540d
COMPONENT_DOWNLOAD_URL= \
    https://github.com/ArtifexSoftware/ghostpdl-downloads/releases/download
COMPONENT_ARCHIVE_URL=  $(COMPONENT_DOWNLOAD_URL)/gs926/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= print/filter/ghostscript
COMPONENT_CLASSIFICATION= System/Printing
COMPONENT_LICENSE=      GPLv3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/configure.mk

PATH=$(PATH.gnu)

# Enforce C standard
CFLAGS   += -std=c99 -D_XOPEN_SOURCE=600 -D__EXTENSIONS__

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

# configure(1) options to use
CONFIGURE_OPTIONS +=	--with-drivers=ALL
CONFIGURE_OPTIONS +=	--with-ijs
CONFIGURE_OPTIONS +=	--with-jbig2dec
CONFIGURE_OPTIONS +=	--enable-cups
CONFIGURE_OPTIONS +=	--enable-dynamic
CONFIGURE_OPTIONS +=	--disable-compile-inits
CONFIGURE_OPTIONS +=	--enable-freetype
CONFIGURE_OPTIONS +=	--with-fontpath=/usr/share/ghostscript/$(COMPONENT_VERSION)/Resource:/usr/share/ghostscript/$(COMPONENT_VERSION)/Resource/Font:/usr/share/ghostscript/fonts:/usr/openwin/lib/X11/fonts/Type1:/usr/openwin/lib/X11/fonts/TrueType:/usr/openwin/lib/X11/fonts/Type3:/usr/X11/lib/X11/fonts/Type1:/usr/X11/lib/fonts/TrueType:/usr/X11/lib/X11/fonts/Type3:/usr/X11/lib/X11/fonts/Resource:/usr/X11/lib/X11/Resource/Font:/usr/share/fonts/TrueType

# configure options to generate 32 bit binaries
$(BUILD_DIR)/$(MACH32)/.configured: CONFIGURE_OPTIONS += CC="$(CC) -m32"
$(BUILD_DIR)/$(MACH32)/ijs/.configured: CONFIGURE_OPTIONS += CC="$(CC) -m32"


# configure options to generate 64 bit binaries
$(BUILD_DIR)/$(MACH64)/.configured: CONFIGURE_OPTIONS += CC="$(CC) -m64"

# config env
CONFIGURE_ENV += LDFLAGS_SO="-shared "
CONFIGURE_ENV += CUPSCONFIG=/usr/bin/cups-config

GS_VARIANT = $(BUILD_DIR)/$(MACH32)
GS_VARIANT_64 = $(BUILD_DIR)/$(MACH64)
IJS_VARIANT = $(BUILD_DIR)/$(MACH32)/ijs
IJS_VARIANT_64 = $(BUILD_DIR)/$(MACH64)/ijs

VARIANTS = $(GS_VARIANT) $(IJS_VARIANT) $(GS_VARIANT_64) $(IJS_VARIANT_64)

# autoconf - Generate configuration scripts
COMPONENT_PREP_ACTION = \
	 (cd $(@D); $(RM) -r libpng zlib jpeg ; autoconf)

$(GS_VARIANT)/.configured: COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

$(GS_VARIANT)/.installed: COMPONENT_INSTALL_TARGETS += \
	install-exec install-so install-scripts install-data \
	install-contrib-extras

$(GS_VARIANT_64)/.configured: COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

$(GS_VARIANT_64)/.installed: COMPONENT_INSTALL_TARGETS += \
	install-exec install-so install-scripts install-data \
	install-contrib-extras

$(IJS_VARIANT)/.configured: COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR)/ijs $(@D); \
	cd $(@D) ; $(ENV) $(CONFIGURE_ENV) ./autogen.sh )

$(IJS_VARIANT_64)/.configured: COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR)/ijs $(@D); \
	cd $(@D) ; $(ENV) $(CONFIGURE_ENV) ./autogen.sh )

CONFIGURE_SCRIPT = ./configure

# build gs and ijs
build: $(VARIANTS:%=%/.built)

# install gs and ijs
install: $(VARIANTS:%=%/.installed)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/toolkit/libxt
