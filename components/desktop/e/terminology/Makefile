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
COMPONENT_VERSION=	0.8.0
COMPONENT_FMRI=     	terminal/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://enlightenment.org
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:7a10d44b023cf6134c2483304e4ad33bea6df0f11266aec482f54fa67a3ce628
COMPONENT_ARCHIVE_URL=	http://download.enlightenment.org/rel/apps/$(COMPONENT_SRC_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_SUMMARY=      Enlightenment - The best terminal emulator written with the EFL

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk


# Need to regenerate configure and Makefiles as 1.13 is used.
COMPONENT_PRE_CONFIGURE_ACTION= pushd $(SOURCE_DIR); aclocal -I m4 --install && autoconf && automake -a; popd;


build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES += library/e/efl
REQUIRED_PACKAGES += library/e/elementary
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
