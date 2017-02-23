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
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		httping
COMPONENT_VERSION=	2.4
COMPONENT_PROJECT_URL=	http://www.vanheusden.com/httping/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:dab59f02b08bfbbc978c005bb16d2db6fe21e1fc841fde96af3d497ddfc82084
COMPONENT_ARCHIVE_URL=	http://www.vanheusden.com/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	13284

TPNO=			21552

BUILD_STYLE= justmake
TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

ifeq ($(OS_VERSION),5.11)
EXTRA_LIBRARIES =	-lsocket -lnsl
endif
EXTRA_LIBRARIES +=	-lncurses -lfftw3 -lssl -lcrypto -lresolv -lm

# The usual Solaris curses.h vs ncurses/curses.h mess.
CFLAGS += -I$(USRINCDIR)/ncurses

# Make 64-bit linking work.
LDFLAGS += $(CC_BITS)

# force enable ncurses support
COMPONENT_BUILD_ARGS += NC=yes
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += OFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ARGS += LDFLAGS="$(LDFLAGS) $(EXTRA_LIBRARIES)"

REQUIRED_PACKAGES += library/fftw-3
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += system/library/math
