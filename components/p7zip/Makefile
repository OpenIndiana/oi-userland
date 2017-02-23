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
BUILD_BITS= 64
# When building with Studio, p7zip has many warnings about extra semicolons,
# and at least one hard error due to an extra semicolon.  It also suffers from
# the pragma pack push/pop problem (15358176).
COMPILER= gcc
include ../../make-rules/shared-macros.mk

ifeq   ($(strip $(PARFAIT_BUILD)),yes)
PATH=$(PARFAIT_TOOLS):$(GCC_ROOT)/bin:$(USRBINDIR)
else
PATH=$(GCC_ROOT)/bin:$(USRBINDIR):$(GNUBIN)
endif

COMPONENT_NAME=		p7zip
COMPONENT_VERSION=	15.14.1
COMPONENT_PROJECT_URL=	http://p7zip.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)_src_all.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:699db4da3621904113e040703220abb1148dfef477b55305e2f14a4f1f8f25d4
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/p7zip/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	2583

TPNO=			27905

BUILD_STYLE= justmake
INSTALL_TARGET=
include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =		$(@D)
COMPONENT_TEST_ENV =		P7ZIP_HOME_DIR=$(BUILD_DIR)/$(MACH$(BITS))/bin
COMPONENT_TEST_TARGETS =	test test_7z test_7zr

COMPONENT_PREP_ACTION = (cd $(@D); cp ../makefile.solaris makefile.machine)
COMPONENT_BUILD_TARGETS = all3
COMPONENT_INSTALL_ARGS += DEST_HOME=$(USRDIR) DEST_DIR=$(PROTO_DIR)

$(SOURCE_DIR)/DOC/copying.txt $(SOURCE_DIR)/DOC/unRarLicense.txt: prep

$(BUILD_DIR)/%: $(SOURCE_DIR)/DOC/%
	$(CP) $< $@

$(BUILD_DIR)/copying.txt: $(SOURCE_DIR)/DOC/copying.txt
	$(CP) $(SOURCE_DIR)/DOC/copying.txt $@

# common targets
EXTRATARGETS = \
	$(BUILD_DIR)/copying.txt $(BUILD_DIR)/unRarLicense.txt

install:	build $(INSTALL_64) $(EXTRATARGETS)

# 7zr.1 is in DOS format for some reason, and geqn can't handle it.
COMPONENT_POST_INSTALL_ACTION += $(GSED) -i -e 's/\r//' $(PROTO_DIR)/usr/man/man1/7zr.1

REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
