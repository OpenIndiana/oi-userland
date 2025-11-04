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
COMPONENT_VERSION =		77.1
COMPONENT_REVISION =		0
COMPONENT_SUMMARY =		International Components for Unicode
COMPONENT_SRC =			$(COMPONENT_NAME)
COMPONENT_ARCHIVE =		icu4c-$(subst .,_,$(HUMAN_VERSION))-src.tgz
COMPONENT_ARCHIVE_HASH =	sha256:588e431f77327c39031ffbb8843c0e3bc122c211374485fa87dc5f3faff24061
COMPONENT_PROJECT_URL =		https://icu.unicode.org/
COMPONENT_ARCHIVE_URL =		https://github.com/unicode-org/icu/releases/download/release-$(subst .,-,$(HUMAN_VERSION))/$(COMPONENT_ARCHIVE)
COMPONENT_VERSION_MAJOR =	$(firstword $(subst ., ,$(HUMAN_VERSION)))
COMPONENT_FMRI =		library/icu-$(COMPONENT_VERSION_MAJOR)
COMPONENT_CLASSIFICATION =	System/Internationalization
COMPONENT_LICENSE =		ICU
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_FMRI.library-32 =	$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.library-32 =	$(COMPONENT_SUMMARY) (32-bit)

# The developer package is published only for the latest (our default) version.
ifeq ($(strip $(COMPONENT_VERSION_MAJOR)),$(strip $(ICU_VERSION)))
COMPONENT_FMRI.developer =	developer/icu
COMPONENT_SUMMARY.developer =	$(COMPONENT_SUMMARY) (development files)
endif

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
CONFIGURE_OPTIONS += --sbindir=$(CONFIGURE_SBINDIR.$(BITS))
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --with-data-packaging=library
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-samples
CONFIGURE_OPTIONS += --enable-renaming

# We do not need common developer files built during 32-bit build.  Such files
# built during the 64-bit built are enough.
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRINCDIR) ;
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRSHAREDIR) ;

# Install additional man pages if we are building the latest (our default)
# version.  Otherwise drop all developer files we do not need.
ifeq ($(strip $(COMPONENT_VERSION_MAJOR)),$(strip $(ICU_VERSION)))
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(INSTALL) -d $(PROTOUSRSHAREMANDIR)/man3lib ; \
	for f in $(COMPONENT_DIR)/files/*.3lib ; do \
		$(INSTALL) $$f $(PROTOUSRSHAREMANDIR)/man3lib/$$(basename $$f) ; \
		$(GSED) -i -e 's/\$$(HUMAN_VERSION)/$(HUMAN_VERSION)/g' $(PROTOUSRSHAREMANDIR)/man3lib/$$(basename $$f) ; \
	done ;
else
# 32-bit counterparts of these are remove unconditionally above
COMPONENT_POST_INSTALL_ACTION.64 += $(RM) -r $(PROTOUSRINCDIR) ;
COMPONENT_POST_INSTALL_ACTION.64 += $(RM) -r $(PROTOUSRSHAREDIR) ;
# Drop rest of dev-only files
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTO_DIR)/$(CONFIGURE_BINDIR.$(BITS))/* ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTO_DIR)/$(CONFIGURE_SBINDIR.$(BITS))/* ;
COMPONENT_POST_INSTALL_ACTION += $(FIND) $(PROTOUSRLIBDIR.$(BITS)) \
	! -name 'libicudata.so.*' \
	! -name 'libicui18n.so.*' \
	! -name 'libicuio.so.*' \
	! -name 'libicuuc.so.*' \
	-exec $(RM) {} \; ;
endif

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
