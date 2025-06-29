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

COMPONENT_NAME=         rage
COMPONENT_VERSION=      0.2.1
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=      Enlightenment - A video and audio player written with the EFL
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://enlightenment.org
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:3dba83ae3d0cdd6c43fc3f6e4ca87ecf58d0481d28cd431ba42c51b82c7b6b1a
COMPONENT_ARCHIVE_URL= 	https://download.enlightenment.org/rel/apps/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         media/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/Sound and Video
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= ( cd $(@D); aclocal -I m4 --install && autoconf && automake -a; )

CONFIGURE_BINDIR.64= $(USRBINDIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/e/efl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
