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
# Copyright 2016 Alexander Pyhalov
# Copyright 2022 Andreas Wacknitz
#

BUILD_BITS=	64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= qpdf
COMPONENT_VERSION= 10.6.3
COMPONENT_SUMMARY= QPDF is a command-line program that does structural, content-preserving transformations on PDF files
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:e8fc23b2a584ea68c963a897515d3eb3129186741dd19d13c86d31fa33493811
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/qpdf/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://qpdf.sourceforge.net/
COMPONENT_FMRI= print/qpdf
COMPONENT_CLASSIFICATION= System/Printing
COMPONENT_LICENSE=      Artistic 2.0
COMPONENT_LICENSE_FILE= Artistic-2.0

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CPPFLAGS += -I/usr/include/pcre
CPPFLAGS += $(CPPFLAGS.$(BITS))

CONFIGURE_OPTIONS += --disable-static

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Remove the line containing date and time when the tests happen:
COMPONENT_TEST_TRANSFORMS += \
	'-e "/STARTING TESTS/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += image/library/libjpeg8-turbo
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
