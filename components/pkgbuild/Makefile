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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BITS=64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pkgbuild
COMPONENT_VERSION=	1.3.105
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:ed32d913af249d4221c2b94450eb4e996747024260c210620e94ac8130bc0fd6
COMPONENT_ARCHIVE_URL=	http://prdownloads.sourceforge.net/pkgbuild/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://pkgbuild.sourceforge.net/
COMPONENT_BUGDB=	utility/pkgbuild

TPNO=			13159

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Required due to patches to configure and/or automake files.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fi;)

ASLR_MODE = $(ASLR_ENABLE)

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

system-test:	$(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += runtime/perl-512
