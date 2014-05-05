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
#

# parfait seems to spin when looking at the .bc files, so
# for now disable it.
PARFAIT_BUILD=no

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         ghostscript
COMPONENT_VERSION=      9.00
COMPONENT_PROJECT_URL=	http://ghostscript.com/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:9e754c315d68d91a65ef208b9a8bda1fb57e45a7be18aa9397acfcc5ff59de16
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)releases/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/ghostscript

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk
include ../../make-rules/configure.mk

PATH=/usr/bin:/usr/gnu/bin

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

# empty test target
test:
	@echo "no tests available"

include ../../make-rules/depend.mk
