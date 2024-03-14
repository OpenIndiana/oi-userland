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
#

BUILD_BITS=			32_and_64
BUILD_SYSTEM=		configure
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		make
COMPONENT_VERSION=	4.3
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/make/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:e05fdde47c5f7ca45cb697e973894ff4f5d79e13b750ed57d7b66d8defc78e19
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/make/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -fi )

COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS += --program-prefix=g
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --with-guile

ASLR_MODE = $(ASLR_ENABLE)

# force re-runs to be the same
COMPONENT_PRE_TEST_ACTION = ( $(TOUCH) $(SOURCE_DIR)/getloadavg.c )

# Strip compilation lines from test output
COMPONENT_TEST_TRANSFORMS += \
    '-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^1-minute.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*load average.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*Running tests for GNU make.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.==========.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^Clearing work.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^config.status: .*$$|XXX_CC_XXX|g" ' \
    '-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
    '-e "/^XXX_CC_XXX$$/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/guile
REQUIRED_PACKAGES += system/library
