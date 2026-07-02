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
# Copyright 2025 Andreas Wacknitz
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= trealla
COMPONENT_VERSION= 2.103.0
COMPONENT_SUMMARY= Trealla prolog is a compact, efficient Prolog interpreter with ISO Prolog aspirations
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL= https://trealla-prolog.github.io/trealla
COMPONENT_ARCHIVE_URL= https://github.com/trealla-prolog/trealla/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:07328da8c75c967d77b60ac381c12723989c165921251608bfccbf767f022bc7
COMPONENT_CLASSIFICATION= Development/System
COMPONENT_FMRI= runtime/$(COMPONENT_NAME)-prolog
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Replace the 0.0.0 with the correct version information
COMPONENT_POST_UNPACK_ACTION += $(GSED) -i -e 's|0\.0\.0|$(COMPONENT_VERSION)|' $(COMPONENT_SRC)/src/version.c ;

# Make sure both x86 and SPARC will work
COMPONENT_PRE_BUILD_ACTION += ( $(GSED) -i -e 's|MACH64|$(MACH64)|' $(COMPONENT_SRC)/Makefile ) ;
# Without cloning the sources we will get links into the source folder
COMPONENT_PRE_BUILD_ACTION += ( CLONEY_MODE=hardlink $(CLONEY) $(SOURCE_DIR) $(@D) ) ;

# Fill the prototype area with the binary and some files from the sources
COMPONENT_POST_INSTALL_ACTION += ( \
	$(MKDIR) -p $(PROTOUSRSHAREDIR)/trealla/docs/samples ; \
	$(CP) $(SOURCE_DIR)/docs/* $(PROTOUSRSHAREDIR)/trealla/docs/ ; \
	$(CP) $(SOURCE_DIR)/samples/* $(PROTOUSRSHAREDIR)/trealla/docs/samples/ ; \
	$(CP) $(SOURCE_DIR)/README.md $(PROTOUSRSHAREDIR)/trealla/docs/ ; ) ;

COMPONENT_TEST_TARGETS = test

# Manually added dependencies
# xxd is being used
REQUIRED_PACKAGES += editor/vim

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
