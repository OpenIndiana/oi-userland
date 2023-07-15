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

# Copyright (c) 2011, 2023, Oracle and/or its affiliates.
# Copyright (c) 2018, Michal Nowak
# Copyright (c) 2022, Friedrich Kink
# Copyright (c) 2023, Andreas Wacknitz
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ghostscript
COMPONENT_VERSION=      10.1.2
HUMAN_VERSION=			10.01.2
NUMERICAL_VERSION=		$(subst .,,$(HUMAN_VERSION))
COMPONENT_SUMMARY=		Ghostscript is an interpreter for the PostScript language and PDF files
COMPONENT_PROJECT_URL=	https://ghostscript.com
COMPONENT_SRC=          $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:48d079242a2ca02a2e47a76a52cdfa818b2ad769c2bab00ad0497dd13560e7e7
COMPONENT_DOWNLOAD_URL= https://github.com/ArtifexSoftware/ghostpdl-downloads/releases/download
COMPONENT_ARCHIVE_URL=  $(COMPONENT_DOWNLOAD_URL)/gs$(NUMERICAL_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= 		print/filter/ghostscript
COMPONENT_CLASSIFICATION= System/Printing
COMPONENT_LICENSE=      AGPLv3, GPL, BSD, MIT, IJG, Apache 2.0

COMPONENT_NAME_1= tessdata_best
COMPONENT_VERSION_1= 4.1.0
COMPONENT_SRC_1= $(COMPONENT_NAME_1)-$(COMPONENT_VERSION_1)
COMPONENT_ARCHIVE_1= $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_URL_1= https://github.com/tesseract-ocr/$(COMPONENT_NAME_1)/archive/refs/tags/$(COMPONENT_ARCHIVE_1)
COMPONENT_ARCHIVE_HASH_1= sha256:bb05b738298ae73e7130e2913ed002b49d94cd1cea508e63be1928fe47770b32

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_UNPACK_ACTION= ( \
	$(RM) $(COMPONENT_LICENSE_FILE) && \
	$(TOUCH) $(COMPONENT_LICENSE_FILE) && \
	for l in $(SOURCE_DIR)/LICENSE $(SOURCE_DIR)/jbig2dec/LICENSE $(SOURCE_DIR)/openjpeg/LICENSE \
	 $(SOURCE_DIR)/libpng/LICENSE $(SOURCE_DIR)/libpng/contrib/gregbook/LICENSE  $(SOURCE_DIR)/zlib/LICENSE \
	 $(SOURCE_DIR)/doc/COPYING $(SOURCE_DIR)/extract/COPYING $(SOURCE_DIR)/lcms2mt/COPYING \
	 $(SOURCE_DIR)/contrib/lxm3200-tweaked/LICENSE  $(SOURCE_DIR)/tesseract/LICENSE ; do \
		$(CAT) $$l >> $(COMPONENT_LICENSE_FILE) ; \
		echo "------------------------------------------------------------" >> $(COMPONENT_LICENSE_FILE) ; \
	done ; )

PATH= $(PATH.gnu)

CFLAGS += $(CPP_XPG6MODE)

# build with the distribution preferred libjpeg implementation
CFLAGS   += $(JPEG_CPPFLAGS) $(JPEG_CFLAGS)
CXXFLAGS += $(JPEG_CPPFLAGS) $(JPEG_CXXFLAGS)
LDFLAGS  += $(JPEG_LDFLAGS)

# configure(1) options to use
CONFIGURE_OPTIONS += --with-drivers=ALL
CONFIGURE_OPTIONS += --with-system-libtiff
CONFIGURE_OPTIONS += --with-ijs
CONFIGURE_OPTIONS += --with-jbig2dec
CONFIGURE_OPTIONS += --enable-cups
CONFIGURE_OPTIONS += --with-libiconv=native
CONFIGURE_OPTIONS += --enable-dynamic
CONFIGURE_OPTIONS += --disable-compile-inits
CONFIGURE_OPTIONS += --disable-hidden-visibility
CONFIGURE_OPTIONS += --enable-freetype
CONFIGURE_OPTIONS += --with-fontpath=/usr/share/ghostscript/$(HUMAN_VERSION)/Resource:/usr/share/ghostscript/$(HUMAN_VERSION)/Resource/Font:/usr/share/ghostscript/fonts:/usr/openwin/lib/X11/fonts/Type1:/usr/openwin/lib/X11/fonts/TrueType:/usr/openwin/lib/X11/fonts/Type3:/usr/X11/lib/X11/fonts/Type1:/usr/X11/lib/fonts/TrueType:/usr/X11/lib/X11/fonts/Type3:/usr/X11/lib/X11/fonts/Resource:/usr/X11/lib/X11/Resource/Font:/usr/share/fonts/TrueType

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

$(IJS_VARIANT)/.configured: BITS=32
	COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR)/ijs $(@D); \
	cd $(@D) ; $(ENV) $(CONFIGURE_ENV) ./autogen.sh )

$(IJS_VARIANT_64)/.configured: BITS=64
	COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR)/ijs $(@D); \
	cd $(@D) ; $(ENV) $(CONFIGURE_ENV) ./autogen.sh )

CONFIGURE_SCRIPT = ./configure

# build gs and ijs
build: $(VARIANTS:%=%/.built)

# install gs and ijs
install: $(VARIANTS:%=%/.installed)

# the license file is dynamically build, thus we need to remove it:
clean::
	$(RM) $(COMPONENT_LICENSE_FILE)

COMPONENT_TEST_CMD = sh $(COMPONENT_DIR)/tests/run
COMPONENT_TEST_ENV += TESSDATA_PREFIX="$(SOURCE_DIR_1)"
COMPONENT_TEST_TRANSFORMS += "-e '/^Using/d'"
COMPONENT_TEST_TRANSFORMS += "-e '/extract.c:.*:extract_subpage_free/d'"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += library/libpaper
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/toolkit/libxt
