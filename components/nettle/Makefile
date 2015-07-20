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
# Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
#

COMPONENT_NAME=		nettle
COMPONENT_VERSION=	3.1
COMPONENT_PROJECT_URL=	http://www.lysator.liu.se/~nisse/nettle/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f6859d4ec88e70805590af9862b4b8c43a2d1fc7991df0a7a711b1e7ca9fc9d3
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/nettle/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/nettle

TPNO=	22160

include ../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS  += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  += --with-include-path=/usr/include/gmp
CONFIGURE_OPTIONS  += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  += CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS  += LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS  += CC_FOR_BUILD="$(CC) $(CC_BITS)"
CONFIGURE_OPTIONS  += --disable-elliptic-curves
CONFIGURE_OPTIONS  += --disable-knuth-lfib

# The additional set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
    '-e "1,/run-tests/d"' \
    '-e "/^e/d"' 

COMPONENT_PREP_ACTION = \
	(cd $(@D) ; ACLOCAL=aclocal-1.11 AUTOMAKE=automake-1.11 autoreconf -fiv)

ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:      $(CONFIGURE_32_and_64)

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
