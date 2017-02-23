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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		bzip2
COMPONENT_VERSION=	1.0.6
COMPONENT_PROJECT_URL=	http://www.bzip.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:a2848f34fcd5d6cf47def00461fcb528a0484d8edef8208d6d2e2909dc61d9cd
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/bzip
COMPONENT_ANITYA_ID=	237

TPNO=			5547

BUILD_STYLE= justmake
# build does this always
SYSTEM_TEST_TARGET= $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/common.mk

LINT_FLAGS +=	-I.

# we need to enable large file support and build PIC for our shared libraries
CFLAGS += $(CPP_LARGEFILES) $(CC_PIC)

# Enable adiheap and adistack security extensions
ADIHEAP_MODE =	$(ADIHEAP_ENABLE)
ADISTACK_MODE =	$(ADISTACK_ENABLE)

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CFLAGS)"
COMPONENT_INSTALL_ARGS += PREFIX=$(PROTOUSRDIR)

COMPONENT_PRE_BUILD_ACTION += \
	(cd $(@D) ; \
	    cp ../../oldapi.c . )

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TARGETS = test
system-test: \
    COMPONENT_TEST_MASTER = \
         $(COMPONENT_TEST_RESULTS_DIR)/system-results-all.master
COMPONENT_SYSTEM_TEST_TARGETS= system-test
COMPONENT_SYSTEM_TEST_DIR = $(SOURCE_DIR)

COMPONENT_TEST_TRANSFORMS += \
    '-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
    '-e "/^XXX_CC_XXX$$/d" '

# common targets
COMPONENT_POST_INSTALL_ACTION.32 += \
	($(INSTALL) $(BUILD_DIR_32)/libbz2.so.1 $(PROTOUSRLIBDIR); \
	cd $(PROTOUSRLIBDIR); rm -f libbz2.so; ln -s libbz2.so.1 libbz2.so);

COMPONENT_PRE_INSTALL_ACTION.64 += $(MKDIR) $(PROTOUSRLIBDIR64);

COMPONENT_POST_INSTALL_ACTION.64 += \
	($(INSTALL) $(BUILD_DIR_64)/libbz2.so.1 $(PROTOUSRLIBDIR64); \
	cd $(PROTOUSRLIBDIR64); rm -f libbz2.so; ln -s libbz2.so.1 libbz2.so;);

REQUIRED_PACKAGES += shell/ksh93
