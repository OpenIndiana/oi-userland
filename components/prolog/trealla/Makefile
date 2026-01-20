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
COMPONENT_VERSION= 2.88.4
COMPONENT_SUMMARY= Trealla prolog is a compact, efficient Prolog interpreter with ISO Prolog aspirations
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL= https://trealla-prolog.github.io/trealla
COMPONENT_ARCHIVE_URL= https://github.com/trealla-prolog/trealla/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:594b4eaf90b9fde9a27dbaec5b922e884ffa89f5ee1ac982d031e341549e3856
COMPONENT_CLASSIFICATION= Development/System
COMPONENT_FMRI= runtime/$(COMPONENT_NAME)-prolog
COMPONENT_LICENSE= MIT

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_BUILD_ACTION += $(GSED) -i -e 's|MACH64|$(MACH64)|' $(COMPONENT_SRC)/Makefile

# Replace the 0.0.0 with the correct version information
COMPONENT_POST_UNPACK_ACTION += $(GSED) -i -e 's|0\.0\.0|$(COMPONENT_VERSION)|' $(COMPONENT_SRC)/src/version.c ;

# Fill the prototype area with the binary and some files from the sources
COMPONENT_POST_INSTALL_ACTION += ( \
	$(MKDIR) -p $(PROTOUSRLIBDIR)/trealla/library ; \
	$(MKDIR) -p $(PROTOUSRLIBDIR)/trealla/docs/samples ; \
	$(CP) $(BUILD_DIR_64)/tpl $(PROTOUSRLIBDIR)/trealla/ ; \
	$(CP) $(BUILD_DIR_64)/library/* $(PROTOUSRLIBDIR)/trealla/library/ ; \
	$(CP) $(SOURCE_DIR)/docs/* $(PROTOUSRLIBDIR)/trealla/docs/ ; \
	$(CP) $(SOURCE_DIR)/samples/* $(PROTOUSRLIBDIR)/trealla/docs/samples/ ; \
	$(CP) $(SOURCE_DIR)/README.md $(PROTOUSRLIBDIR)/trealla/docs/ ; ) ;

# Manually added dependencies
TEST_REQUIRED_PACKAGES += developer/debug/valgrind
# xxd is being used
REQUIRED_PACKAGES += editor/vim

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
