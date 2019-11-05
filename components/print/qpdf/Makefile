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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= qpdf
COMPONENT_VERSION= 6.0.0
COMPONENT_SUMMARY= QPDF is a command-line program that does structural, content-preserving transformations on PDF files
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:a9fdc7e94d38fcd3831f37b6e0fe36492bf79aa6d54f8f66062cf7f9c4155233
COMPONENT_ARCHIVE_URL= \
  http://downloads.sourceforge.net/qpdf/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://qpdf.sourceforge.net/
COMPONENT_FMRI= print/qpdf
COMPONENT_CLASSIFICATION= System/Printing
COMPONENT_LICENSE=      Artistic 2.0
COMPONENT_LICENSE_FILE= Artistic-2.0


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CPPFLAGS.32 = -D_FILE_OFFSET_BITS=64

CPPFLAGS += -I/usr/include/pcre
CPPFLAGS += $(CPPFLAGS.$(BITS))

CONFIGURE_OPTIONS += --disable-static

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

#64-bit tests fail
test: $(TEST_32_and_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
