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
# Copyright 2023 Andreas Wacknitz
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	libcupsfilters
COMPONENT_VERSION= 2.1.1
COMPONENT_SUMMARY= libcupsfilters contains all the code of the filters of the former cups-filters package as library functions
COMPONENT_DESCRIPTION= The filter functions are principally intended to be used for the data format conversion tasks needed in \
					   Printer Applications. They are already in use (together with libppd and pappl-retrofit) by the CUPS-driver \
					   retro-fitting Printer Applications from OpenPrinting. \
					   In addition to the filter functions libcupsfilters also contains several API functions useful for \
					   developing printer drivers/Printer Applications, like image and raster graphics handling, \
					   make/model/device ID matching, ...
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:6c303e36cfde05a6c88fb940c62b6a18e7cdbfb91f077733ebc98f104925ce36
COMPONENT_PROJECT_URL= https://openprinting.github.io/
COMPONENT_ARCHIVE_URL= https://github.com/OpenPrinting/$(COMPONENT_NAME)/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	print/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Printing
COMPONENT_LICENSE= Apache-2.0-with-GPL2-LGPL2-Exception
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D) )

COMPONENT_PREP_ACTION += ( cd $(@D); PATH=$(PATH) $(CONFIG_SHELL) autogen.sh )

CPPFLAGS = -D_POSIX_PTHREAD_SEMANTICS
CPPFLAGS += -I/usr/include/cups
CPPFLAGS += -I/usr/include/lcms2

CFLAGS += $(XPG6MODE)

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-poppler
CONFIGURE_OPTIONS += --with-test-font-path=/usr/share/fonts/TrueType/dejavu/DejaVuSans.ttf
# We don't have mutool (https://mupdf.readthedocs.io/en/latest/mupdf-command-line.html).
CONFIGURE_OPTIONS += --disable-mutool

COMPONENT_BUILD_ENV   += PATH="$(PATH.gnu)"
COMPONENT_INSTALL_ENV += PATH="$(PATH.gnu)"
COMPONENT_TEST_ENV    += libtool_install_magic='%%%MAGIC variable%%%'
COMPONENT_TEST_ENV    += libtool_execute_magic='%%%MAGIC variable%%%'

# Manually added dependencies
TEST_REQUIRED_PACKAGES += system/font/truetype/dejavu

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(JPEG_IMPLEM_PKG)
REQUIRED_PACKAGES += image/library/libexif
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += image/library/libtiff
REQUIRED_PACKAGES += library/lcms2
REQUIRED_PACKAGES += library/libpoppler
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += print/qpdf
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/libdbus
REQUIRED_PACKAGES += system/library/math
