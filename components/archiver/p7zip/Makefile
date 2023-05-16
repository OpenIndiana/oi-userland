#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2016, Jim Klimov
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         p7zip
COMPONENT_VERSION=      16.2
HUMAN_VERSION=		16.02
COMPONENT_REVISION=     5
COMPONENT_SUMMARY=      The p7zip compression and archiving utility
COMPONENT_PROJECT_URL=  https://p7zip.sourceforge.net/
COMPONENT_SRC=          $(COMPONENT_NAME)_$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC)_src_all.tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:5eb20ac0e2944f6cb9c2d51dd6c4518941c185347d4089ea89087ffdd6e2341f
COMPONENT_ARCHIVE_URL=	https://downloads.sourceforge.net/project/p7zip/p7zip/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         compress/p7zip
COMPONENT_CLASSIFICATION= System/Core

include $(WS_MAKE_RULES)/common.mk


COMPONENT_TEST_DIR =           $(@D)
COMPONENT_TEST_ENV =           P7ZIP_HOME_DIR=$(BUILD_DIR)/$(MACH$(BITS))/bin
COMPONENT_TEST_TARGETS =       test test_7z test_7zr

COMPONENT_PREP_ACTION = (cd $(@D) && \
	$(GSED) -e 's,^CC=,\#CC=,' -e 's,^CXX=,\#CXX=,' -e 's,-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE,$$(BUILD_FLAGS),' < makefile.solaris_x86 > makefile.machine && \
	( echo 'CC=$$(BUILD_CC) $$(ALLFLAGS)'; echo 'CXX=$$(BUILD_CXX) $$(ALLFLAGS)' ) >> makefile.machine )

COMPONENT_BUILD_TARGETS = all3
COMPONENT_INSTALL_ARGS += DEST_HOME=/usr DEST_DIR=$(PROTO_DIR)

COMPONENT_BUILD_ARGS += BUILD_CC="$(CC)"
# Note: the -std=c++11 setting below is probably not needed for a newer version.
COMPONENT_BUILD_ARGS += BUILD_CXX="$(CXX) -std=c++11"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ARGS += BUILD_FLAGS="$(CPP_LARGEFILES) $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS)"

$(SOURCE_DIR)/DOC/copying.txt $(SOURCE_DIR)/DOC/unRarLicense.txt: prep

$(BUILD_DIR)/%: $(SOURCE_DIR)/DOC/%
	$(CP) $< $@

EXTRATARGETS = \
	$(BUILD_DIR)/copying.txt $(BUILD_DIR)/unRarLicense.txt

COMPONENT_POST_INSTALL_ACTION = \
	( $(MKDIR) $(PROTOUSRLIBDIR)/p7zip/$(MACH$(BITS)) \
	  && $(MV) $(PROTOUSRLIBDIR)/p7zip/7z* $(PROTOUSRLIBDIR)/p7zip/$(MACH$(BITS))/ \
	  && $(MV) $(PROTOUSRLIBDIR)/p7zip/Codecs $(PROTOUSRLIBDIR)/p7zip/$(MACH$(BITS))/ \
	) ;

install:	build $(INSTALL_64) $(EXTRATARGETS)

# When p7zip's install target is run, it creates all its directories mode 555,
# so they're impossible to remove without adding the write bit first.
COMPONENT_POST_INSTALL_ACTION += $(CHMOD) -R u+w $(PROTO_DIR)

# build does this always

REQUIRED_PACKAGES += system/library/math

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
