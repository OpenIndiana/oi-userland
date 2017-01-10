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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
# libtool only delivers scripts that embed paths, so prefer 32-bit.
BUILD_BITS= 32_and_64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libtool
COMPONENT_VERSION=	2.4.6
COMPONENT_ARCHIVE_HASH=	\
    sha256:e3bd4d5d3d025a36c21dd6af7ea818a2afcd4dfc1ea5a17b39d7854bcd0c06e3
COMPONENT_BUGDB=	utility/libtool

TPNO=			24542

BUILD_TARGET=
INSTALL_TARGET=
include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		PERL="$(PERL)"

COMPONENT_PREP_ACTION = (cd $(@D) ; \
	touch $(SOURCE_DIR)/README-release ; \
	MAKE=/usr/bin/gmake ./bootstrap --force --no-git)
# Remove the hard-wired compiler locations in the LTCC and CC line
# in the version of the libtool script.
COMPONENT_POST_INSTALL_ACTION = \
	cd $(PROTO_DIR)$(USRBIN.$(BITS)); \
	$(GSED) -i \
		-e 's|^LTCC="/.*$$|LTCC="cc"|' \
		-e 's|^CC="/.*$$|CC="cc"|' libtool ; \

# When this component is updated, a full Userland build should
# be performed in a test BE with the new version of libtool installed
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/^===/p" ' \
	'-e "/failed/p" ' \
	'-e "/passed/p" '

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

REQUIRED_PACKAGES += developer/base-developer-utilities
REQUIRED_PACKAGES += developer/gnu-binutils
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += text/gnu-grep
REQUIRED_PACKAGES += text/gnu-sed
