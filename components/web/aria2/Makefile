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
# Copyright (c) 2016 Predrag Zečević
# Copyright (c) 2020 Michal Nowak
#

BUILD_BITS= 64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			aria2
COMPONENT_VERSION=		1.37.0
COMPONENT_SUMMARY=		aria2 - lightweight multi-protocol and multi-source download utility
COMPONENT_PROJECT_URL=	https://aria2.github.io/
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:60a420ad7085eb616cb6e2bdf0a7206d68ff3d37fb5a956dc44242eb2f79b66b
COMPONENT_ARCHIVE_URL=	https://github.com/aria2/aria2/releases/download/release-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			web/aria2
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE=		GPLv3

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

LDFLAGS += -lsocket -lnsl

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-ca-bundle=/etc/certs/ca-certificates.crt
CONFIGURE_OPTIONS += --with-bashcompletiondir=/usr/share/bash-completion/completions/

CONFIGURE_ENV += LD_OPTIONS="$(LD_OPTIONS)"

COMPONENT_TEST_ENV += LD_OPTIONS="$(LD_OPTIONS)"

# We have one failing test (from test-suite.log):
# 09/26 19:19:47 [INFO] Processing metaurl group metaurl=README.torrent
# 09/26 19:19:47 [ERROR] Unrecognized URI or unsupported protocol: README.torrent

# cppunit is for tests
REQUIRED_PACKAGES += developer/cppunit

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/gnutls-3
REQUIRED_PACKAGES += library/libcares
REQUIRED_PACKAGES += library/libssh2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/nettle
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
