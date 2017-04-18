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

COMPONENT_NAME=         ephoto
COMPONENT_VERSION=      0.0.1
COMPONENT_FMRI=         image/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/Sound and Video
COMPONENT_SUMMARY=      Ephoto
COMPONENT_PROJECT_URL=  http://enlightenment.org
COMPONENT_GIT_DATE= 		20170418
COMPONENT_GIT_HASH= 	  4f7874b403c098d9258fde7b6c415db1b4ae0740
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_GIT_HASH)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:8781102afeb82b894b7c6d7118499b9a782fef14e7cb007162092274d86c1116
COMPONENT_ARCHIVE_URL= \
    https://git.enlightenment.org/apps/ephoto.git/snapshot/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION= \
    ( cd $(@D); NOCONFIGURE=1 ./autogen.sh; )

CONFIGURE_BINDIR.64=$(USRBINDIR)

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/e/efl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
