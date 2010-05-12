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
BUILD_VERSION =	5.11-0.140

COMPILER =		studio
BITS =			32
PYTHON_VERSION =	2.6

TOOLS =		$(WS_TOP)/tools
WS_LOGS =	$(WS_TOP)/logs
MAKE_RULES =	$(WS_TOP)/components/make-rules

PKG_REPO =	file://$(WS_TOP)/repo
PROTO_DIR =	$(shell pwd)/$(COMPONENT_SRC)/installed-prototype

CONSTANT_TIME =	LD_PRELOAD=$(TOOLS)/time.o

MACH64 =	$(shell isainfo -k)

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
