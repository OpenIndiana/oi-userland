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
# Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
#

CONSOLIDATION =	userland
PUBLISHER =	$(CONSOLIDATION)-build

# get the most recent build number from the last mercurial tag
LAST_HG_TAG =	$(shell hg tags -q | head -2 | tail -1)
LAST_BUILD_NUM = $(LAST_HG_TAG:build-%=%)

OS_VERSION =		$(shell uname -r)
SOLARIS_VERSION =	$(OS_VERSION:5.%=2.%)
BUILD_NUM =		0.$(shell expr $(LAST_BUILD_NUM) + 1)
BUILD_VERSION =		$(OS_VERSION)-$(BUILD_NUM)

COMPILER =		studio
BITS =			32
PYTHON_VERSION =	2.6

TOOLS =		$(WS_TOP)/tools
WS_LOGS =	$(WS_TOP)/logs
MAKE_RULES =	$(WS_TOP)/components/make-rules

PKG_REPO =	file://$(WS_TOP)/repo
PROTO_DIR =	$(shell pwd)/$(COMPONENT_SRC)/installed-prototype-$(MACH)

# work around _TIME, _DATE, embedded date chatter in component builds
# to use, set TIME_CONSTANT in the component Makefile and add $(CONSTANT_TIME)
# to the appropriate {CONFIGURE|BUILD|INSTALL}_ENV
CONSTANT_TIME =		LD_PRELOAD_32=$(TOOLS)/time-$(MACH32).so
CONSTANT_TIME +=	LD_PRELOAD_64=$(TOOLS)/time-$(MACH64).so
CONSTANT_TIME +=	TIME_CONSTANT=$(TIME_CONSTANT)

# set MACH from uname -p to either sparc or i386
MACH =		$(shell uname -p)

# set MACH32 from MACH to either sparcv7 or i86
MACH32_1 =	$(MACH:sparc=sparcv7)
MACH32 =	$(MACH32_1:i386=i86)

# set MACH64 from MACH to either sparcv9 or amd64
MACH64_1 =	$(MACH:sparc=sparcv9)
MACH64 =	$(MACH64_1:i386=amd64)

BUILD_32 =		$(COMPONENT_SRC)/build-$(MACH32)/.built
BUILD_64 =		$(COMPONENT_SRC)/build-$(MACH64)/.built
BUILD_32_and_64 =	$(BUILD_32) $(BUILD_64)

INSTALL_32 =		$(COMPONENT_SRC)/build-$(MACH32)/.installed
INSTALL_64 =		$(COMPONENT_SRC)/build-$(MACH64)/.installed
INSTALL_32_and_64 =	$(INSTALL_32) $(INSTALL_64)

SPRO_ROOT =	/opt/sunstudio12.1
GCC_ROOT =	/usr/gnu

CC.studio.32 =	$(SPRO_ROOT)/bin/cc -m32
CCC.studio.32 =	$(SPRO_ROOT)/bin/CC -m32

CC.studio.64 =	$(SPRO_ROOT)/bin/cc -m64
CCC.studio.64 =	$(SPRO_ROOT)/bin/CC -m64

CC.gcc.32 =	$(GCC_ROOT)/bin/cc -m32
CCC.gcc.32 =	$(GCC_ROOT)/bin/CC -m32

CC.gcc.64 =	$(GCC_ROOT)/bin/cc -m64
CCC.gcc.64 =	$(GCC_ROOT)/bin/CC -m64

CC =		$(CC.$(COMPILER).$(BITS))
CCC =		$(CCC.$(COMPILER).$(BITS))

LD =		/usr/bin/ld

PYTHON.2.4.32 =	/usr/bin/python2.4
PYTHON.2.4.64 =	/usr/bin/amd64/python2.4

PYTHON.2.6.32 =	/usr/bin/python2.6
PYTHON.2.6.64 =	/usr/bin/amd64/python2.6

PYTHON.32 =	$(PYTHON.$(PYTHON_VERSION).$(BITS))
PYTHON.64 =	$(PYTHON.$(PYTHON_VERSION).$(BITS))

GMAKE =		/usr/gnu/bin/make
GPATCH =	/usr/gnu/bin/patch
GPATCH_FLAGS =	-p1 -b

PKGSEND =	/usr/bin/pkgsend

TOUCH =		/usr/bin/touch
MKDIR =		/bin/mkdir -p
RM =		/bin/rm -f
CP =		/bin/cp -f
ENV =		/usr/bin/env
