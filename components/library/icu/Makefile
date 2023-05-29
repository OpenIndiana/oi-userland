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
# Copyright 2017 Alexander Pyhalov
# Copyright 2021, 2023 Andreas Wacknitz
#

BUILD_BITS= 64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= icu
COMPONENT_VERSION= 72.1
COMPONENT_UVERSION= 72_1
COMPONENT_DVERSION= 72-1
COMPONENT_SUMMARY= International Components for Unicode
COMPONENT_SRC= $(COMPONENT_NAME)
COMPONENT_ARCHIVE= icu4c-$(COMPONENT_UVERSION)-src.tgz
COMPONENT_ARCHIVE_HASH=	sha256:a2d2d38217092a7ed56635e34467f92f976b370e20182ad325edea6681a71d68
COMPONENT_PROJECT_URL = https://icu-project.org
COMPONENT_ARCHIVE_URL = https://github.com/unicode-org/icu/releases/download/release-$(COMPONENT_DVERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=		icu
COMPONENT_LICENSE_FILE=	icu/LICENSE

include $(WS_MAKE_RULES)/common.mk

# The build system does not honor the environment variables
PATH = $(GCC_BINDIR):$(PATH.gnu)

# set relocate_to option while unpacking the tar ball
UNPACK_ARGS= -r $(COMPONENT_SRC)

COMPONENT_BUILD_TARGETS = all

CONFIGURE_SCRIPT = $(SOURCE_DIR)/icu/source/runConfigureICU

CONFIGURE_OPTIONS = Solaris/GCC
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --with-data-packaging=library
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-samples
CONFIGURE_OPTIONS += --disable-renaming
CONFIGURE_OPTIONS += --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))

CFLAGS += -D__EXTENSIONS__ -DDECCHECK -D_XOPEN_SOURCE=600
CXXFLAGS += -D__EXTENSIONS__ -DDECCHECK -D_XOPEN_SOURCE=600 -std=c++11

COMPONENT_POST_CONFIGURE_ACTION = \
	(echo 'CPPFLAGS += -DICU_DATA_DIR=\"$(CONFIGURE_PREFIX)/share/icu/$(COMPONENT_VERSION)\"' >> $(@D)/icudefs.mk ) 

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
    '-n ' \
    '-e "/^All tests OK:  testdata intltest iotest cintltst/p" ' \
    '-e "/^PASS: config selfcheck OK/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
