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
COMPONENT_VERSION =		74.2
COMPONENT_SUMMARY =		International Components for Unicode
COMPONENT_SRC =			$(COMPONENT_NAME)
COMPONENT_ARCHIVE =		icu4c-$(subst .,_,$(HUMAN_VERSION))-src.tgz
COMPONENT_ARCHIVE_HASH =	sha256:5e4fb11d6a3e6b85afb55de8da8a71538f1d8fd64fce893986b37d60e5bb0091
COMPONENT_PROJECT_URL =		https://icu.unicode.org/
COMPONENT_ARCHIVE_URL =		https://github.com/unicode-org/icu/releases/download/release-$(subst .,-,$(HUMAN_VERSION))/$(COMPONENT_ARCHIVE)
COMPONENT_VERSION_MAJOR =	$(word 1,$(subst ., ,$(HUMAN_VERSION)))
COMPONENT_FMRI =		library/icu-$(COMPONENT_VERSION_MAJOR)
COMPONENT_CLASSIFICATION =	System/Internationalization
COMPONENT_LICENSE =		ICU
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_FMRI.library-32 =	$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.library-32 =	$(COMPONENT_SUMMARY) (32-bit)

COMPONENT_FMRI.developer =	developer/icu
COMPONENT_SUMMARY.developer =	$(COMPONENT_SUMMARY) (development files)

include $(WS_MAKE_RULES)/common.mk

# Testing expects GNU diff in PATH
PATH = $(PATH.gnu)

# Workaround for https://unicode-org.atlassian.net/browse/ICU-22632
COMPONENT_POST_UNPACK_ACTION += \
	$(RM) $(SOURCE_DIR)/LICENSE ; \
	$(CP) $(COMPONENT_DIR)/files/LICENSE $(SOURCE_DIR) ;

COMPONENT_BUILD_TARGETS = all

CONFIGURE_SCRIPT = $(SOURCE_DIR)/source/runConfigureICU

CONFIGURE_OPTIONS = Solaris/GCC
CONFIGURE_OPTIONS += --prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS += --bindir=$(CONFIGURE_BINDIR.$(BITS))
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --with-data-packaging=library
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-samples
CONFIGURE_OPTIONS += --enable-renaming

# Install additional man pages
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) -d $(PROTOUSRSHAREMANDIR)/man3lib ; \
	for f in $(COMPONENT_DIR)/files/*.3lib ; do \
		$(INSTALL) $$f $(PROTOUSRSHAREMANDIR)/man3lib/$$(basename $$f) ; \
		$(GSED) -i -e 's/\$$(HUMAN_VERSION)/$(HUMAN_VERSION)/g' $(PROTOUSRSHAREMANDIR)/man3lib/$$(basename $$f) ; \
	done

# Tests fails when compiled using gcc 13
# https://unicode-org.atlassian.net/browse/ICU-22629
COMPONENT_TEST_TRANSFORMS += \
    '-n ' \
    '-e "/^All tests OK:  testdata intltest iotest cintltst/p" ' \
    '-e "/^PASS: config selfcheck OK/p" '

# Replace COMPONENT_VERSION_MAJOR in library symlink path
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's|^\(link .*path=usr/lib/.*lib.*\.so\.\)$(COMPONENT_VERSION_MAJOR) |\1$$(COMPONENT_VERSION_MAJOR) |'
PKG_MACROS += COMPONENT_VERSION_MAJOR=$(COMPONENT_VERSION_MAJOR)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
