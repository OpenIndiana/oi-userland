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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		httping
COMPONENT_VERSION=	2.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.vanheusden.com/httping/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	\
    sha256:dab59f02b08bfbbc978c005bb16d2db6fe21e1fc841fde96af3d497ddfc82084
COMPONENT_ARCHIVE_URL=	http://www.vanheusden.com/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/httping

TPNO=			21552

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPILER =	gcc

CC +=		$(CC_BITS)

COMPONENT_BUILD_ARGS +=	LDFLAGS="$(LDFLAGS) -lfftw3 -lssl -lcrypto -lresolv -lm"
COMPONENT_BUILD_ENV += CC="$(CC)"

ASLR_MODE = $(ASLR_ENABLE)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += library/fftw-3
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/security/openssl/openssl-fips-140
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
