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
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tcpdump
COMPONENT_VERSION=	4.7.4
COMPONENT_PROJECT_URL=	http://www.tcpdump.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5a321f0fb959b928f26112c9f49f81d754c23c1d8ffb0feb69304fee06b77e0a
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)release/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/tcpdump

# Prevent macro redefinition error 
CFLAGS += -D _NETINET_IP_H

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# fix my alignment issues instead of falling over on sparc
studio_ALIGN.sparc.64=-xmemalign=16i
CONFIGURE_OPTIONS.sparc += ac_cv___attribute__=no
CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(MACH))

# lazyloading (indirectly enabled by -Bdirect) seems to cause problems with
# libpcap device enumeration.
LD_B_DIRECT=

CONFIGURE_OPTIONS += --enable-ipv6=yes
CONFIGURE_OPTIONS += --with-user=nobody
CONFIGURE_OPTIONS += --without-crypto

ASLR_MODE = $(ASLR_ENABLE)

# Master test results are the same for both 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

COMPONENT_PRE_TEST_ACTION = \
        ($(CP) -r $(SOURCE_DIR)/tests $(@D)/.)

test:		$(TEST_32_and_64)


BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
