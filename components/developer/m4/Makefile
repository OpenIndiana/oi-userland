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
# Copyright 2017, Aurelien Larcher.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		m4
COMPONENT_VERSION=	1.4.18
COMPONENT_FMRI=	developer/macro/gnu-m4
COMPONENT_SUMMARY=	GNU m4
COMPONENT_CLASSIFICATION=	Development/GNU
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/m4/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ab2633921a5cd38e48797bf5521ad259bdc4b979078034a3b790d7fec5493fab
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/m4/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3, FDLv1.2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_PREFIX =	/usr/gnu
CONFIGURE_OPTIONS  +=	--infodir=$(CONFIGURE_INFODIR)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
 	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libsigsegv
REQUIRED_PACKAGES += system/library
