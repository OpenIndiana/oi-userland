#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved. 
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	          spidermonkey
COMPONENT_VERSION=        1.8.5
COMPONENT_REVISION=       1
COMPONENT_SUMMARY=        Javascript engine
COMPONENT_PROJECT_URL=    https://developer.mozilla.org/en-US/docs/Mozilla/Projects/SpiderMonkey
COMPONENT_FMRI=	          library/spidermonkey
COMPONENT_CLASSIFICATION= Development/Other Languages
COMPONENT_SRC=            js-1.8.5
COMPONENT_ARCHIVE=	      js185-1.0.0.tar.gz
COMPONENT_ARCHIVE_URL=    http://ftp.mozilla.org/pub/mozilla.org/js/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	  sha256:5d12f7e1f5b4a99436685d97b9b7b75f094d33580227aa998c406bbae6f2a687
COMPONENT_LICENSE=	      MPL 2.0

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_POST_UNPACK_ACTION = ( \
	$(MV) $(SOURCE_DIR)/js/src/* $(SOURCE_DIR); \
  cd $(SOURCE_DIR) && autoconf-2.13; \
	$(RM) -r $(SOURCE_DIR)/js; \
	$(RM) -r $(SOURCE_DIR)/patches )

COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CXXFLAGS += -D_GLIBCXX_USE_C99_MATH -D__C99FEATURES__=1 -D__EXTENSIONS__
LDFLAGS += -B direct -z ignore -R/usr/lib/mps -L/usr/lib/mps

CONFIGURE_OPTIONS += --srcdir=$(BUILD_DIR_32)
CONFIGURE_OPTIONS += --with-nspr-cflags='-I/usr/include/mps' 
CONFIGURE_OPTIONS += --with-nspr-libs="-L/usr/lib/mps -lnspr4 -lplds4 -lplc4 -ldl -lposix4"
CONFIGURE_OPTIONS += --enable-threadsafe
CONFIGURE_OPTIONS += --with-pthreads
CONFIGURE_OPTIONS += --disable-pedantic
CONFIGURE_OPTIONS += --enable-install-strip
CONFIGURE_OPTIONS += --enable-ctypes
CONFIGURE_OPTIONS += --enable-readline
CONFIGURE_OPTIONS += --with-x

COMPONENT_TEST_TRANSFORMS= "'/^PASSED ALL/'"
COMPONENT_TEST_TRANSFORMER= $(NAWK)
#
# Spidermonkey is 32bit only, testing with 64bit dies at the first test
#
build:    $(BUILD_32)

install:  $(INSTALL_32)

test:     $(TEST_32)


REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/nspr
REQUIRED_PACKAGES += library/nspr/header-nspr
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += developer/build/autoconf-213

