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
# Copyright (c) 2025, Klaus Ziegler
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

ENV = /usr/bin/env

COMPONENT_NAME=         p7zip
COMPONENT_VERSION=      17.6
HUMAN_VERSION=		17.06
COMPONENT_REVISION=     1
COMPONENT_SUMMARY=      The p7zip compression and archiving utility
COMPONENT_PROJECT_URL=  https://github.com/p7zip-project/p7zip
COMPONENT_SRC=          $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=      v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c35640020e8f044b425d9c18e1808ff9206dc7caf77c9720f57eb0849d714cd1
COMPONENT_ARCHIVE_URL=	https://github.com/p7zip-project/p7zip/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         compress/p7zip
COMPONENT_CLASSIFICATION= System/Core

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =           $(@D)
COMPONENT_TEST_ENV =           P7ZIP_HOME_DIR=$(BUILD_DIR)/$(MACH$(BITS))/bin
COMPONENT_TEST_TARGETS =       test test_7z test_7zr

# make COMPONENT_PREP_ACTION architecture independent.
ifeq ($(MACH), sparc)
ARCH= $(MACH)_gcc
else
ARCH= x86
endif

COMPONENT_PREP_ACTION = (cd $(@D) && \
	$(GSED) -e 's,^CC=,\#CC=,' -e 's,^CXX=,\#CXX=,' -e 's,-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE,$$(BUILD_FLAGS),' < makefile.solaris_$(ARCH) > makefile.machine && \
	( echo 'CC=$$(BUILD_CC) $$(ALLFLAGS)'; echo 'CXX=$$(BUILD_CXX) $$(ALLFLAGS)' ) >> makefile.machine )

COMPONENT_BUILD_TARGETS = all3
COMPONENT_INSTALL_ARGS += DEST_HOME=/usr DEST_DIR=$(PROTO_DIR)

COMPONENT_BUILD_ARGS += BUILD_CC="$(CC)"
COMPONENT_BUILD_ARGS += BUILD_CXX="$(CXX)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ARGS += BUILD_FLAGS="$(CPP_LARGEFILES) $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS)"

$(SOURCE_DIR)/DOC/copying.txt $(SOURCE_DIR)/DOC/unRarLicense.txt: prep

$(BUILD_DIR)/%: $(SOURCE_DIR)/DOC/%
	$(CP) $< $@

EXTRATARGETS = \
	$(BUILD_DIR)/copying.txt $(BUILD_DIR)/unRarLicense.txt

COMPONENT_PRE_INSTALL_ACTION = cd $(COMPONENT_SRC); $(GPATCH) -p1 < ../files/07-fix-$(MACH64)-lib-path.patch

COMPONENT_POST_INSTALL_ACTION = \
	( $(MKDIR) $(PROTOUSRLIBDIR)/p7zip/$(MACH$(BITS)) \
	  && $(MV) $(PROTOUSRLIBDIR)/p7zip/7z* $(PROTOUSRLIBDIR)/p7zip/$(MACH$(BITS))/ \
	  && $(MV) $(PROTOUSRLIBDIR)/p7zip/Codecs $(PROTOUSRLIBDIR)/p7zip/$(MACH$(BITS))/ \
	) ;

install:	build $(INSTALL_64) $(EXTRATARGETS)

# When p7zip's install target is run, it creates all its directories mode 555,
# so they're impossible to remove without adding the write bit first.
COMPONENT_POST_INSTALL_ACTION += $(CHMOD) -R u+w $(PROTO_DIR) ;

COMPONENT_TEST_TRANSFORMS += '-e "/^REP=/d" '
COMPONENT_TEST_TRANSFORMS += '-e "/^Comment = /d" '
COMPONENT_TEST_TRANSFORMS += '-e "/^Modified = /d" '
COMPONENT_TEST_TRANSFORMS += '-e "/^Created = /d" '
COMPONENT_TEST_TRANSFORMS += '-e "/^Compressed: /d" '
COMPONENT_TEST_TRANSFORMS += '-e "/^Headers Size = /d" '
COMPONENT_TEST_TRANSFORMS += '-e "/^Physical Size = /d" '
COMPONENT_TEST_TRANSFORMS += '-e "/^1 file,/d" '
COMPONENT_TEST_TRANSFORMS += '-e "/^Archive size: /d" '


ifeq ($(strip $(MACH)),sparc)
REQUIRED_PACKAGES += system/library/math
endif

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
