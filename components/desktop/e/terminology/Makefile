#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2015, Aurelien Larcher. All rights reserved.
#
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		terminology
COMPONENT_VERSION=      1.1.0
COMPONENT_REVISION=		1
COMPONENT_SUMMARY= Enlightenment - The best terminal emulator written with the EFL
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://www.enlightenment.org/about-terminology
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:eb9136e487ab9e6ff3c98173919b5ad105626434d096dafecd18392fc40c348f
COMPONENT_ARCHIVE_URL=  https://download.enlightenment.org/rel/apps/terminology/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=     	terminal/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_LICENSE=      BSD 2-clause
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_BINDIR.64= $(USRBINDIR)

COMPONENT_PREP_ACTION= ( cd $(@D); aclocal -I m4 --install && autoconf && automake -a; )

# Auto-generated dependencies
REQUIRED_PACKAGES += library/e/efl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
