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
USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		icu
COMPONENT_VERSION =		72.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		International Components for Unicode
COMPONENT_SRC =			$(COMPONENT_NAME)
COMPONENT_ARCHIVE =		icu4c-$(subst .,_,$(HUMAN_VERSION))-src.tgz
COMPONENT_ARCHIVE_HASH =	sha256:a2d2d38217092a7ed56635e34467f92f976b370e20182ad325edea6681a71d68
COMPONENT_PROJECT_URL =		https://icu.unicode.org/
COMPONENT_ARCHIVE_URL =		https://github.com/unicode-org/icu/releases/download/release-$(subst .,-,$(HUMAN_VERSION))/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION =	System/Internationalization
COMPONENT_FMRI =		library/icu
COMPONENT_LICENSE =		ICU
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Testing expects GNU diff in PATH
PATH = $(PATH.gnu)

PATCH_LEVEL = 2

COMPONENT_BUILD_TARGETS = all

CONFIGURE_SCRIPT = $(SOURCE_DIR)/source/runConfigureICU

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

# Install additional man pages
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -d $(PROTOUSRSHAREMANDIR)/man3lib ;
COMPONENT_POST_INSTALL_ACTION += \
	for f in $(COMPONENT_DIR)/files/*.3lib ; do \
		$(INSTALL) $$f $(PROTOUSRSHAREMANDIR)/man3lib/$$(basename $$f) ; \
		$(GSED) -i -e 's/\$$(HUMAN_VERSION)/$(HUMAN_VERSION)/g' $(PROTOUSRSHAREMANDIR)/man3lib/$$(basename $$f) ; \
	done

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
