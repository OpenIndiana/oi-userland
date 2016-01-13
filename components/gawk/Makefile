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

COMPONENT_NAME=		gawk
COMPONENT_VERSION=	4.1.3
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/gawk/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:e3cf55e91e31ea2845f8338bedd91e40671fc30e4d82ea147d220e687abda625
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/gawk/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gawk

# The additional gawk specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
        '-e "s|\(^/usr/gnu/bin/make\).*|\1|" ' 

TPNO=			26217	

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_BINDIR.64 =   $(CONFIGURE_PREFIX)/bin
CONFIGURE_LIBDIR.64 =   $(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS	+=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS	+=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS	+=	CFLAGS="$(CFLAGS)"

COMPONENT_SYSTEM_TEST_ARGS = AWKPROG=/usr/bin/gawk

ASLR_MODE = $(ASLR_ENABLE)


configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# must build tests before using
system-test:    build $(SYSTEM_TEST_64)

REQUIRED_PACKAGES += library/libsigsegv
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
