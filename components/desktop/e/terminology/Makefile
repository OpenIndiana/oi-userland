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
COMPONENT_VERSION=	1.0.0
COMPONENT_FMRI=     	terminal/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SUMMARY= Enlightenment - The best terminal emulator written with the EFL
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://enlightenment.org
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:cc31f0648c83ad8374d35ef60c255eb0a5f1de156ff2567afc6b5b5ef751a45e
COMPONENT_ARCHIVE_URL=	http://download.enlightenment.org/rel/apps/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_BINDIR.64=$(USRBINDIR)

COMPONENT_PREP_ACTION= \
    ( cd $(@D); aclocal -I m4 --install && autoconf && automake -a; )

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/e/efl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
