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
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		mrtg
COMPONENT_VERSION=	2.16.2
COMPONENT_PROJECT_URL=	http://oss.oetiker.ch/mrtg
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:ce9ec97bb6c8f94a8d8bb2d3cfa7e72b73754ed7a1081e7aca1c8cece5ce3385
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/pub/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/mrtg

TPNO=			9225

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure-64.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --with-gd-inc=/usr/include/gd2
CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS) -I$(BUILD_DIR_64)/bin"
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS) $(CC_BITS)"

CONFIGURE_BINDIR.64 = $(USRBINDIR)
CONFIGURE_LIBDIR.64 = $(USRLIBDIR)

# Build process expects a bin directory in compilation area.
COMPONENT_PRE_BUILD_ACTION=(cd $(@D) ; mkdir -p bin)

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

system-test:	$(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/gd
REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
