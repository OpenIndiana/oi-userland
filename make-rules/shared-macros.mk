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

PATH=/usr/bin:/usr/gnu/bin

CONSOLIDATION =	userland
PUBLISHER =	$(CONSOLIDATION)-build

IS_GLOBAL_ZONE =	$(shell /usr/sbin/zoneadm list | grep -c global)
ROOT =			/

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
PYTHON_VERSIONS =	2.4 2.6

WS_LOGS =	$(WS_TOP)/logs
WS_REPO =	$(WS_TOP)/repo
WS_TOOLS =	$(WS_TOP)/tools
WS_MAKE_RULES =	$(WS_TOP)/make-rules
WS_COMPONENTS =	$(WS_TOP)/components
WS_INCORPORATIONS =	$(WS_TOP)/incorporations
WS_LINT_CACHE =	$(WS_TOP)/cache

BASS_O_MATIC =	$(WS_TOOLS)/bass-o-matic

PKG_REPO =	file:$(WS_REPO)
PROTO_DIR =	$(shell pwd)/$(COMPONENT_SRC)/installed-prototype-$(MACH)

SFWBIN =	/usr/sfw/bin
SFWLIB =	/usr/sfw/lib
PROTOSFWBIN =	$(PROTO_DIR)/$(SFWBIN)
PROTOSFWLIB =	$(PROTO_DIR)/$(SFWLIB)

# work around _TIME, _DATE, embedded date chatter in component builds
# to use, set TIME_CONSTANT in the component Makefile and add $(CONSTANT_TIME)
# to the appropriate {CONFIGURE|BUILD|INSTALL}_ENV
CONSTANT_TIME =		LD_PRELOAD_32=$(WS_TOOLS)/time-$(MACH32).so
CONSTANT_TIME +=	LD_PRELOAD_64=$(WS_TOOLS)/time-$(MACH64).so
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

# BUILD_TOOLS is the root of all tools not normally installed on the system.
BUILD_TOOLS =	/ws/onnv-tools

SPRO_ROOT =	$(BUILD_TOOLS)/SUNWspro
SPRO_VROOT =	$(SPRO_ROOT)/sunstudio12.1

GCC_ROOT =	/usr/gnu

CC.studio.32 =	$(SPRO_VROOT)/bin/cc -m32
CCC.studio.32 =	$(SPRO_VROOT)/bin/CC -m32

CC.studio.64 =	$(SPRO_VROOT)/bin/cc -m64
CCC.studio.64 =	$(SPRO_VROOT)/bin/CC -m64

CC.gcc.32 =	$(GCC_ROOT)/bin/cc -m32
CCC.gcc.32 =	$(GCC_ROOT)/bin/CC -m32

CC.gcc.64 =	$(GCC_ROOT)/bin/cc -m64
CCC.gcc.64 =	$(GCC_ROOT)/bin/CC -m64

CC =		$(CC.$(COMPILER).$(BITS))
CCC =		$(CCC.$(COMPILER).$(BITS))

LD =		/usr/bin/ld

PYTHON.2.4.32 =	/usr/bin/python2.4
PYTHON.2.4.64 =	/usr/bin/$(MACH64)/python2.4

PYTHON.2.6.32 =	/usr/bin/python2.6
PYTHON.2.6.64 =	/usr/bin/$(MACH64)/python2.6

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
LN =		/bin/ln
SYMLINK =	/bin/ln -s
ENV =		/usr/bin/env
INSTALL =	/usr/bin/ginstall
