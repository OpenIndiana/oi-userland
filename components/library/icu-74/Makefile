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
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		International Components for Unicode
COMPONENT_SRC =			$(COMPONENT_NAME)
COMPONENT_ARCHIVE =		icu4c-$(subst .,_,$(HUMAN_VERSION))-src.tgz
COMPONENT_ARCHIVE_HASH =	sha256:68db082212a96d6f53e35d60f47d38b962e9f9d207a74cfac78029ae8ff5e08c
COMPONENT_PROJECT_URL =		https://icu.unicode.org/
COMPONENT_ARCHIVE_URL =		https://github.com/unicode-org/icu/releases/download/release-$(subst .,-,$(HUMAN_VERSION))/$(COMPONENT_ARCHIVE)
COMPONENT_VERSION_MAJOR =	$(firstword $(subst ., ,$(HUMAN_VERSION)))
COMPONENT_FMRI =		library/icu-$(COMPONENT_VERSION_MAJOR)
COMPONENT_CLASSIFICATION =	System/Internationalization
COMPONENT_LICENSE =		ICU
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_FMRI.library-32 =	$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.library-32 =	$(COMPONENT_SUMMARY) (32-bit)

include $(WS_MAKE_RULES)/common.mk

# Testing expects GNU diff in PATH
PATH = $(PATH.gnu)

# https://unicode-org.atlassian.net/browse/ICU-22629
CXXFLAGS += -fexcess-precision=fast

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

COMPONENT_TEST_TRANSFORMS += \
    '-n ' \
    '-e "/^All tests OK:  testdata intltest iotest cintltst/p" ' \
    '-e "/^PASS: config selfcheck OK/p" '

# Replace COMPONENT_VERSION_MAJOR in library symlink path
GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's|^\(link .*path=usr/lib/.*lib.*\.so\.\)$(COMPONENT_VERSION_MAJOR) |\1$$(COMPONENT_VERSION_MAJOR) |'
PKG_MACROS += COMPONENT_VERSION_MAJOR=$(COMPONENT_VERSION_MAJOR)

# Sanity check
ifneq ($(strip $(COMPONENT_FMRI.developer)),)
ifneq ($(strip $(COMPONENT_VERSION_MAJOR)),$(strip $(ICU_VERSION)))
$(error ICU_VERSION does not match developer/icu version)
endif
endif

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
