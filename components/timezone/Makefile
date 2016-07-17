#
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
# Copyright (c) 2005, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= NO_ARCH
include ../../make-rules/shared-macros.mk

COMPONENT_NAME= 	timezone
COMPONENT_VERSION=    	2016.6
COMPONENT_SRC=
HUMAN_VERSION=		2016f
TPNO=			24870

# Build info part of pkg(5) FMRI dropped ",$(OS_VERSION)" between 11 and 12;
# needed for evaluation repo where we build the default repo from 12 on 11.
ifeq ($(OS_VERSION),5.11)
OS_META_VERSION=	,$(OS_VERSION)-$(OS_VERSION)
else
OS_META_VERSION=	-$(OS_VERSION)
endif

# "etcetera" must be listed before "backward" because it sets up links that
# "backward" needs.
TZFILES= africa antarctica asia australasia etcetera europe \
	 factory northamerica pacificnew \
	 southamerica backward

BUILD_STYLE= archive
COMMON_TARGETS= no
include $(WS_MAKE_RULES)/common.mk

PKG_MACROS +=		OS_META_VERSION=$(OS_META_VERSION)

POFILE=zoneinfo.po

CLEAN_PATHS += $(POFILE)

build:
	@/bin/sh ./do_pofile.sh > $(POFILE)

install: build
	/usr/sbin/zic -d $(PROTOUSRSHARELIBDIR)/zoneinfo $(TZFILES)

# empty test target
test:	$(NO_TESTS)

system-test:    $(NO_TESTS)

