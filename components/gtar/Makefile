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
BUILD_BITS= 64
# parfait fails to compile us (21334808)
export PARFAIT_BUILD=no
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tar
COMPONENT_VERSION=	1.28
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:60e4bfe0602fef34cd908d91cf638e17eeb09394d7b98c2487217dc4d3147562
COMPONENT_BUGDB=	utility/gtar
COMPONENT_ANITYA_ID=	4939

TPNO=			23088

SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

PATCH_LEVEL=0

# tests (ttyemu.c) requires c99
studio_C99MODE = $(studio_C99_ENABLE)

# Use ssh (rather than rsh) for remote commands.
CONFIGURE_ENV += "RSH=/usr/bin/ssh"

CONFIGURE_BINDIR.64=	$(GNUBIN)
CONFIGURE_MANDIR=	$(GNUSHAREMAN)

CONFIGURE_OPTIONS +=	--with-rmt=$(USRSBINDIR)/rmt
CONFIGURE_OPTIONS +=	--libexecdir=$(USRSBINDIR)

COMPONENT_SYSTEM_TEST_DIR = $(BUILD_DIR_64)/tests
COMPONENT_SYSTEM_TEST_TARGETS =  installcheck-local

# Remove everything except test output.
COMPONENT_TEST_TRANSFORMS = \
	'-e "/^\#\# ----/,/tests were skipped\./p" ' \
	'-e "/.*/d" '

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/gzip
REQUIRED_PACKAGES += network/ssh
REQUIRED_PACKAGES += system/core-os
