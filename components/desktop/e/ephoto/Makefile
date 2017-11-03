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
# Copyright (c) 2015-2017, Aurelien Larcher. All rights reserved.
#
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=         ephoto
COMPONENT_VERSION=      1.5
COMPONENT_FMRI=         image/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Applications/Sound and Video
COMPONENT_SUMMARY=      Ephoto
COMPONENT_DESCRIPTION=  A comprehensive image viewer based on the EFL
COMPONENT_PROJECT_URL=  http://www.smhouston.us/ephoto
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
    sha256:ffd5e42a309bb3bbb70010938a7065ed553901937784078cd1c66ba707897412
COMPONENT_ARCHIVE_URL= \
    http://www.smhouston.us/stuff/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION= \
    ( cd $(@D); NOCONFIGURE=1 ./autogen.sh; )

CONFIGURE_OPTIONS+= --disable-dependency-tracking

CONFIGURE_BINDIR.64=$(USRBINDIR)

build: $(BUILD_64)

install: $(INSTALL_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/e/efl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
