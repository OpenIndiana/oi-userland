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

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		m4
COMPONENT_VERSION=	1.4.19
COMPONENT_REVISION=	1
COMPONENT_FMRI=	developer/macro/gnu-m4
COMPONENT_SUMMARY=	GNU m4
COMPONENT_CLASSIFICATION=	Development/GNU
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/m4/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:3be4a26d825ffdfda52a56fc43246456989a3630093cced3fbddf4771ee58a70
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/m4/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3, FDLv1.2

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

ASLR_MODE = $(ASLR_ENABLE)

CONFIGURE_PREFIX =	/usr/gnu
CONFIGURE_OPTIONS  +=	--infodir=$(CONFIGURE_INFODIR)

# Note that stackovf.test may fail on SPARC platform.
# The update of libsigsegv library might resolve this failure.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# The Makefile in the checks directory has different targets for the
# equivalent of "gmake test" and "gmake system-test".
COMPONENT_TEST_DIR =            $(@D)/checks
COMPONENT_TEST_TARGETS =        check-local

COMPONENT_SYSTEM_TEST_DIR =     $(@D)/checks
COMPONENT_SYSTEM_TEST_TARGETS = installcheck

COMPONENT_TEST_TRANSFORMS += \
		'-e "/^Making check.*/d"' \
    	'-e "/ GEN /d"' \
    	'-e "/No differences/d"' \
    	'-e "/^PATH=/d"' \
    	'-e "/^m4/d"' \
    	'-e "/m4-tmp/d"' \
    	'-e "/Killed/d"' \
    	'-e "/^make/d"'

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
