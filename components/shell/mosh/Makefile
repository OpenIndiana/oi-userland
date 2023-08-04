#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2015, Predrag Zecevic. All rights reserved.
#
BUILD_BITS=			64
USE_OPENSSL11=		yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mosh
COMPONENT_VERSION=	1.4.0
COMPONENT_REVISION= 1
COMPONENT_SUMMARY=	Mosh (mobile shell) - Remote terminal application that allows roaming, supports intermittent connectivity, and provides intelligent local echo and line editing of user keystrokes (replacement for SSH).
COMPONENT_PROJECT_URL=	https://mosh.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:ae581fbddf038730af9eee4d319a483288395a0722d0c94c7efb7fdbdbb0dbac
COMPONENT_ARCHIVE_URL=	https://github.com/mobile-shell/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	service/network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Security
COMPONENT_LICENSE=      GPLv3+

TEST_TARGET=		$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# The archive contains an uncommon base folder name, fix it:
COMPONENT_POST_UNPACK_ACTION= ( $(MV) $(COMPONENT_NAME)-$(COMPONENT_SRC) $(COMPONENT_SRC) )

COMPONENT_PREP_ACTION= ( cd $(@D); sh autogen.sh )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--enable-examples
CONFIGURE_OPTIONS+=	--enable-completion
CONFIGURE_OPTIONS+=	--with-utempter

# Manually added build dependencies
REQUIRED_PACKAGES += utility/bash-completion 

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/c++/protobuf
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libutempter
REQUIRED_PACKAGES += system/library/math
