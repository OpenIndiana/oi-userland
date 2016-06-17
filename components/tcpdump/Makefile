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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		tcpdump
COMPONENT_VERSION=	4.7.4
COMPONENT_PROJECT_URL=	http://www.tcpdump.org/
COMPONENT_ARCHIVE_HASH=	\
    sha256:5a321f0fb959b928f26112c9f49f81d754c23c1d8ffb0feb69304fee06b77e0a
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)release/$(COMPONENT_ARCHIVE)

TPNO=			22949

include $(WS_MAKE_RULES)/common.mk

ifeq ($(OS_VERSION),5.11)
# Prevent macro redefinition error
CFLAGS += -D _NETINET_IP_H
endif

# Rebuild the configure script so the man pages are normalized.
COMPONENT_PREP_ACTION = (cd $(@D); autoconf);

# fix my alignment issues instead of falling over on sparc
studio_ALIGN.sparc.64=-xmemalign=16i
CONFIGURE_OPTIONS.sparc += ac_cv___attribute__=no

# lazyloading (indirectly enabled by -Bdirect) seems to cause problems with
# libpcap device enumeration.
LD_B_DIRECT=

CONFIGURE_OPTIONS += --enable-ipv6=yes
CONFIGURE_OPTIONS += --with-user=nobody
CONFIGURE_OPTIONS += --without-crypto

# common targets
COMPONENT_PRE_TEST_ACTION = \
        ($(CP) -r $(SOURCE_DIR)/tests $(@D)/.)

REQUIRED_PACKAGES += system/library/libpcap
