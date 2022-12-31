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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2016, Aurelien Larcher. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2021, Andreas Wacknitz
#

BUILD_BITS=	64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= mpc
COMPONENT_VERSION= 1.3.1
COMPONENT_SUMMARY= Multiprecision complex data type evaluation library
COMPONENT_PROJECT_URL= https://www.multiprecision.org/
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= https://ftp.gnu.org/gnu/mpc/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:ab642492f5cf882b74aa0cb730cd410a81edcdbec895183ce930e706c1c759b8
COMPONENT_SIG_URL= $(COMPONENT_ARCHIVE_URL).sig
COMPONENT_FMRI= library/mpc
COMPONENT_CLASSIFICATION= Development/High Performance Computing
COMPONENT_LICENSE= LGPLv2.1

include $(WS_MAKE_RULES)/common.mk

CFLAGS += `pkg-config --cflags mpfr`

CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --disable-static

COMPONENT_TEST_DIR= $(BUILD_DIR)/$(MACH$(BITS))/tests

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/mpfr
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
