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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		mtr
COMPONENT_VERSION=	0.86
COMPONENT_PROJECT_URL=	http://www.bitwizard.nl/mtr/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:7912f049f9506748913e2866068b7f95b11a4e0a855322120b456c46ac9eb763
COMPONENT_ARCHIVE_URL=	https://github.com/traviscross/mtr/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_BUGDB=	utility/mtr

TPNO=			18130

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_SBINDIR.64 =		$(CONFIGURE_PREFIX)/bin
CONFIGURE_OPTIONS  +=		--without-gtk
CONFIGURE_OPTIONS  +=		--without-ipinfo
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  +=		LDFLAGS="$(LDFLAGS) $(CC_BITS)"

COMPONENT_PRE_CONFIGURE_ACTION += (cd $(SOURCE_DIR); ./bootstrap.sh)

ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
