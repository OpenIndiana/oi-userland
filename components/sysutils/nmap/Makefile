
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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2016 Jim Klimov
# Copyright 2022 Nona Hansel
#

BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 		nmap
COMPONENT_VERSION=		7.80
COMPONENT_REVISION=		2
COMPONENT_PROJECT_URL=	http://nmap.org/
COMPONENT_FMRI=			diagnostic/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_SUMMARY=		Network exploration tool and security / port scanner
COMPONENT_DESCRIPTION=	Nmap is useful for inventorying the network, managing \
service upgrade schedules, and monitoring host or service uptime
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:fcfa5a0e42099e12e4bf7a68ebe6fde05553383a682e816a7ec9256ab4773faa
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)dist/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=	$(COMPONENT_PROJECT_URL)dist/sigs/$(COMPONENT_ARCHIVE).asc	
COMPONENT_LICENSE=		GPLv2,OpenSSL,SSLeay
# Note: This license file incorporates nmap COPYING and OpenSSL license text
COMPONENT_LICENSE_FILE=	nmap.license

include $(WS_MAKE_RULES)/common.mk

PKG_OPTIONS +=	-D COMPONENT_DESCRIPTION="$(COMPONENT_DESCRIPTION)"

COMPONENT_PREP_ACTION = (cd $(@D)/libdnet-stripped && autoconf)

COMPONENT_PRE_CONFIGURE_ACTION = $(CP) -rp $(SOURCE_DIR)/. $(@D)

CONFIGURE_OPTIONS  +=   CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_OPTIONS  +=   LIBS="-lsocket -lnsl"
CONFIGURE_OPTIONS  +=   --srcdir=$(BUILD_DIR_$(BITS))
CONFIGURE_OPTIONS  +=   --localstatedir=/var
CONFIGURE_OPTIONS  +=   --without-localdirs
CONFIGURE_OPTIONS  +=   --without-ndiff
CONFIGURE_OPTIONS  +=   --without-zenmap
CONFIGURE_OPTIONS  +=   --with-openssl
CONFIGURE_OPTIONS  +=   --with-libpcap
CONFIGURE_OPTIONS  +=   --with-libpcre
CONFIGURE_OPTIONS  +=   --with-liblua
CONFIGURE_OPTIONS  +=   --with-ncat

TEST_TARGET= $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/libssh2
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua-53
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
