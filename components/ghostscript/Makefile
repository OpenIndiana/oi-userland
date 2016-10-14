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

#
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
# parfait seems to spin when looking at the .bc files (13704877), so
# for now disable it.
export PARFAIT_BUILD=no

# Prefer 32-bit due to ghostcript's hybrid build system.
BUILD_BITS= 32_and_64
include ../../make-rules/shared-macros.mk


COMPONENT_NAME=         ghostscript
COMPONENT_VERSION=      9.00
COMPONENT_PROJECT_URL=	http://ghostscript.com/
COMPONENT_ARCHIVE_HASH= \
    sha256:9e754c315d68d91a65ef208b9a8bda1fb57e45a7be18aa9397acfcc5ff59de16
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)releases/$(COMPONENT_ARCHIVE)

TPNO=			3796

COMMON_TARGETS= no
include $(WS_MAKE_RULES)/common.mk

PATH=$(SPRO_VROOT)/bin:$(USRBINDIR):$(GNUBIN)

# ghostscript uses a non-standard hybrid-build to build both 32 and 64-bit;
# override these to prevent build failure.
CC_FOR_BUILD=
CONFIGURE_CPPFLAGS=

# configure(1) options to use
CONFIGURE_OPTIONS +=	--with-drivers=ALL
CONFIGURE_OPTIONS +=	--with-ijs
CONFIGURE_OPTIONS +=	--without-omni
CONFIGURE_OPTIONS +=	--with-jbig2dec
CONFIGURE_OPTIONS +=	--with-jasper
CONFIGURE_OPTIONS +=	--enable-cups
CONFIGURE_OPTIONS +=	--enable-dynamic
CONFIGURE_OPTIONS +=	--disable-compile-inits
CONFIGURE_OPTIONS +=	--disable-freetype
CONFIGURE_OPTIONS +=	--with-fontpath=/usr/share/ghostscript/$(COMPONENT_VERSION)/Resource:/usr/share/ghostscript/$(COMPONENT_VERSION)/Resource/Font:/usr/share/ghostscript/fonts:/usr/openwin/lib/X11/fonts/Type1:/usr/openwin/lib/X11/fonts/TrueType:/usr/openwin/lib/X11/fonts/Type3:/usr/X11/lib/X11/fonts/Type1:/usr/X11/lib/fonts/TrueType:/usr/X11/lib/X11/fonts/Type3:/usr/X11/lib/X11/fonts/Resource:/usr/X11/lib/X11/Resource/Font

# configure options to generate 64 bit binaries
$(BUILD_DIR)/$(MACH64)/.configured: CONFIGURE_OPTIONS += CC="$(CC) -m64"
$(BUILD_DIR)/$(MACH64)/ijs/.configured: CONFIGURE_OPTIONS += CC="$(CC) -m64"

# config env
CONFIGURE_ENV += LDFLAGS_SO="-G"
CONFIGURE_ENV += CUPSCONFIG=$(USRBINDIR)/cups-config

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

# Adjust '#!/usr/bin/perl'
PERL_SCRIPTS= $(PROTOUSRBINDIR)/fixmswrd.pl

# ASLR disabled until sufficient testing can be performed.
ASLR_MODE= $(ASLR_DISABLE)

# configure gs and ijs
configure: $(VARIANTS:%=%/.configured)

# build gs and ijs
build: $(VARIANTS:%=%/.built)

# install gs and ijs
install: $(VARIANTS:%=%/.installed)

test:	$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += image/library/libjpeg
REQUIRED_PACKAGES += image/library/libpng
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += print/cups
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxcursor
REQUIRED_PACKAGES += x11/library/toolkit/libxt
