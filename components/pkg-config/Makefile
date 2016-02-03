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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		pkg-config
COMPONENT_VERSION=	0.29
COMPONENT_PROJECT_URL=	http://www.freedesktop.org/wiki/Software/pkg-config
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:c8507705d2a10c67f385d66ca2aae31e81770cc0734b4191eb8c489e864a006b
COMPONENT_ARCHIVE_URL=	http://pkgconfig.freedesktop.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_ARCHIVE_URL).asc
COMPONENT_BUGDB=	utility/pkg-config

TPNO=			26453

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# otherwise our default PKG_CONFIG_PATH will change to the 64-bit libdir
CONFIGURE_LIBDIR.64 =   $(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)" 
COMPONENT_TEST_ENV += PATH=/usr/gnu/bin:/usr/bin
ASLR_MODE = $(ASLR_ENABLE)

# The additional pkg-config specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
	'-e "/^+ sed -e /d" '

ifeq ($(OS_VERSION),5.11)
OLD_DESKTOP_BUILD=	0.175.2.0.0.21.0
else
OLD_DESKTOP_BUILD=	5.12.0.0.0.25.0
endif

PKG_MACROS +=		OLD_DESKTOP_BUILD=$(OLD_DESKTOP_BUILD)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
