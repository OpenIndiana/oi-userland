#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 (c) Aurelien Larcher. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		flac
COMPONENT_VERSION=	1.4.3
COMPONENT_REVISION=	4
COMPONENT_SUMMARY=	An Open Source Lossless Audio Codec
COMPONENT_PROJECT_URL=	https://xiph.org/flac
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:6c58e69cd22348f441b861092b825e591d0b822e106de6eb0ee4d05d27205b70
COMPONENT_ARCHIVE_URL=	https://downloads.us.xiph.org/releases/flac/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		codec/flac
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_LICENSE=	Xiph.org BSD-style, binaries & media player plugins also use GPL v2, LGPL v2.1, documentation uses FDL v1.2

COMPONENT_FMRI.library=		$(COMPONENT_FMRI)-$(subst .,,$(basename $(HUMAN_VERSION)))
COMPONENT_SUMMARY.library=	$(COMPONENT_SUMMARY) (runtime libraries)

include $(WS_MAKE_RULES)/common.mk

# helper target
update-license-file: patch
	( \
		printf -- '--- COPYING.FDL -----------------------------------------------------------\n\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.FDL ; \
		printf '\n\n--- COPYING.GPL -----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.GPL ; \
		printf '\n\n--- COPYING.LGPL ----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.LGPL ; \
		printf -- '--- COPYING.Xiph ----------------------------------------------------------\n\n' ; \
		$(CAT) $(SOURCE_DIR)/COPYING.Xiph \
	) > $(COMPONENT_DIR)/$(COMPONENT_LICENSE_FILE)

CXXFLAGS += -fstack-protector-all

CONFIGURE_OPTIONS += --enable-ogg
CONFIGURE_OPTIONS += --disable-doxygen-docs

ifeq   ($(MACH), i386)
CONFIGURE_OPTIONS += --enable-sse
CONFIGURE_OPTIONS += --disable-asm-optimizations
else
CONFIGURE_OPTIONS += --disable-sse
CONFIGURE_OPTIONS += --disable-asm-optimizations
endif

# We do not need to distribute binaries.  We cannot use '--disable-programs'
# configure option because flac and metaflac are needed to run tests.
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRBINDIR) ;
# We do not need developer files
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRINCDIR) ;
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRSHAREDIR) ;
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOPKGCONFIGDIR.$(BITS)) ;
COMPONENT_POST_INSTALL_ACTION += $(FIND) $(PROTO_DIR) -name '*.so' -exec $(RM) {} \; ;

# Note that the test needed to be run with standard user privileges.
COMPONENT_TEST_TRANSFORMS = \
	' -n ' \
	' -e "/unit test/p" ' \
	' -e "/---/p" ' \
	' -e "/passed/p" ' \
	' -e "/+++/p" ' \
	' -e "/PASSED/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libogg
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
