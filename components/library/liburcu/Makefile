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
# Copyright (c) 2026 Friedrich Kink. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		liburcu
COMPONENT_VERSION=	0.15.6
COMPONENT_SUMMARY=      Userspace RCU
COMPONENT_DESCRIPTION=  liburcu is a userspace RCU (read-copy-update) library. This data \
                        synchronization library provides read-side access which scales \
                        linearly with the number of cores.
COMPONENT_PROJECT_URL=	https://liburcu.org/
COMPONENT_ARCHIVE_HASH=	sha256:850b192096eb11ebf2c70e8f97bc7da7479ee41da1bebeb44e3986908bac414f
COMPONENT_SRC=          userspace-rcu-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	userspace-rcu-$(HUMAN_VERSION).tar.bz2
COMPONENT_ARCHIVE_URL=	https://lttng.org/files/urcu/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/liburcu
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= LICENSES/LGPL-2.1-or-later.txt

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_CONFIGURE_ACTION = ( \
        $(GSED) -i -e '/endian/a \#elif defined(__sun__)\n\#include <endian.h>' $(SOURCE_DIR)/doc/examples/rculfhash/jhash.h )

CFLAGS += 	     -D__sun__

CONFIGURE_OPTIONS += --disable-dependency-tracking
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-compiler-tls
CONFIGURE_OPTIONS += --enable-compiler-atomic-builtins
CONFIGURE_OPTIONS += --enable-Werror

COMPONENT_TEST_TRANSFORMS = \
        '-e "/^\/usr/d" ' \
        '-e "/^make/d" ' \
        '-e "/^Making/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
