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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		patchutils
COMPONENT_VERSION=	0.3.1
IPS_PKG_NAME=		text/patchutils
COMPONENT_PROJECT_URL=	http://cyberelk.net/tim/patchutils/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:48d28d4a6fd9922e15ecfd8a152ba5aef6673842c8303337fcaa6b3bb2d129a2
COMPONENT_ARCHIVE_URL=	http://cyberelk.net/tim/data/patchutils/stable/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/patchutils

TPNO=			9269

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"

# Commands go under /usr/bin so set bindir correctly.
CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin

ASLR_MODE = $(ASLR_ENABLE)

# A couple of tests dump core, and the message contains the pid
# A number of failing tests operate on randomly named files
# Remove the make garbage from the test output
COMPONENT_TEST_TRANSFORMS += \
	'-e "/coredump/s/[0-9]*: Abort/XXXX: Abort/"' \
	'-e "s,\(/var/tmp//.*diff-1\.\)......,\1XXXXXX,"' \
	'-e "1,/^for test in/{N;d}"' \
	'-e "/^===/{N;N;q}"'

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

# Note that the gendiff tests will fail on Solaris, because the gendiff utility
# is missing; this is delivered by rpm.
test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += text/gnu-diffutils
REQUIRED_PACKAGES += text/gnu-patch
