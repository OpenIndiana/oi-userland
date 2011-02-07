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
# Copyright (c) 2010, 2011, Oracle and/or its affiliates. All rights reserved.
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
PYTHON_VERSIONS =	2.6

WS_LOGS =	$(WS_TOP)/logs
WS_REPO =	$(WS_TOP)/repo
WS_TOOLS =	$(WS_TOP)/tools
WS_MAKE_RULES =	$(WS_TOP)/make-rules
WS_COMPONENTS =	$(WS_TOP)/components
WS_INCORPORATIONS =	$(WS_TOP)/incorporations
WS_LINT_CACHE =	$(WS_TOP)/pkglint-cache

BASS_O_MATIC =	$(WS_TOOLS)/bass-o-matic

PKG_REPO =	file:$(WS_REPO)

COMPONENT_DIR =	$(shell pwd)
SOURCE_DIR =	$(COMPONENT_DIR)/$(COMPONENT_SRC)
BUILD_DIR =	$(COMPONENT_DIR)/build
PROTO_DIR =	$(BUILD_DIR)/prototype/$(MACH)

USRDIR =	/usr
BINDIR =	/bin
LIBDIR =	/lib
USRBINDIR =	$(USRDIR)/bin
USRLIBDIR =	$(USRDIR)/lib
USRSHAREDIR =	$(USRDIR)/share
USRSHAREMANDIR =	$(USRSHAREDIR)/man
USRSHAREMAN1DIR =	$(USRSHAREMANDIR)/man1
USRSHAREMAN3DIR =	$(USRSHAREMANDIR)/man3
USRSHAREMAN5DIR =	$(USRSHAREMANDIR)/man5
USRLIBDIR64 =	$(USRDIR)/lib/$(MACH64)
PROTOUSRDIR =	$(PROTO_DIR)/$(USRDIR)
PROTOUSRBINDIR =	$(PROTO_DIR)/$(USRBINDIR)
PROTOUSRLIBDIR =	$(PROTO_DIR)/$(USRLIBDIR)
PROTOUSRLIBDIR64 =	$(PROTO_DIR)/$(USRLIBDIR64)
PROTOUSRSHAREDIR =	$(PROTO_DIR)/$(USRSHAREDIR)
PROTOUSRSHAREMANDIR =	$(PROTO_DIR)/$(USRSHAREMANDIR)
PROTOUSRSHAREMAN1DIR =	$(PROTO_DIR)/$(USRSHAREMAN1DIR)
PROTOUSRSHAREMAN3DIR =	$(PROTO_DIR)/$(USRSHAREMAN3DIR)


SFWBIN =	/usr/sfw/bin
SFWLIB =	/usr/sfw/lib
SFWSHARE =	/usr/sfw/share
SFWSHAREMAN =	/usr/sfw/share/man
SFWSHAREMAN1 =	/usr/sfw/share/man/man1
PROTOSFWBIN =	$(PROTO_DIR)/$(SFWBIN)
PROTOSFWLIB =	$(PROTO_DIR)/$(SFWLIB)
PROTOSFWSHARE =	$(PROTO_DIR)/$(SFWSHARE)
PROTOSFWSHAREMAN =	$(PROTO_DIR)/$(SFWSHAREMAN)
PROTOSFWSHAREMAN1 =	$(PROTO_DIR)/$(SFWSHAREMAN1)

GNUBIN =	/usr/gnu/bin
GNUSHARE =	/usr/gnu/share
GNUSHAREMAN =	/usr/gnu/share/man
GNUSHAREMAN1 =	/usr/gnu/share/man/man1
PROTOGNUBIN =	$(PROTO_DIR)/$(GNUBIN)
PROTOGNUSHARE =	$(PROTO_DIR)/$(GNUSHARE)
PROTOGNUSHAREMAN =	$(PROTO_DIR)/$(GNUSHAREMAN)
PROTOGNUSHAREMAN1 =	$(PROTO_DIR)/$(GNUSHAREMAN1)

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

BUILD_DIR_32 =		$(BUILD_DIR)/$(MACH32)
BUILD_DIR_64 =		$(BUILD_DIR)/$(MACH64)

BUILD_32 =		$(BUILD_DIR_32)/.built
BUILD_64 =		$(BUILD_DIR_64)/.built
BUILD_32_and_64 =	$(BUILD_32) $(BUILD_64)

INSTALL_32 =		$(BUILD_DIR_32)/.installed
INSTALL_64 =		$(BUILD_DIR_64)/.installed
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

lint.32 =	$(SPRO_VROOT)/bin/lint -m32
lint.64 =	$(SPRO_VROOT)/bin/lint -m64

LINT =		$(lint.$(BITS))

LD =		/usr/bin/ld

PYTHON.2.6.32 =	/usr/bin/python2.6
PYTHON.2.6.64 =	/usr/bin/$(MACH64)/python2.6

PYTHON.32 =	$(PYTHON.$(PYTHON_VERSION).$(BITS))
PYTHON.64 =	$(PYTHON.$(PYTHON_VERSION).$(BITS))

GMAKE =		/usr/gnu/bin/make
GPATCH =	/usr/gnu/bin/patch
GPATCH_FLAGS =	-p1 -b

PKGSEND =	/usr/bin/pkgsend
PKGLINT =	/usr/bin/pkglint

TOUCH =		/usr/bin/touch
MKDIR =		/bin/mkdir -p
RM =		/bin/rm -f
CP =		/bin/cp -f
LN =		/bin/ln
SYMLINK =	/bin/ln -s
ENV =		/usr/bin/env
INSTALL =	/usr/bin/ginstall

INS.dir=        $(INSTALL) -d $@
INS.file=       $(INSTALL) -m 444 $< $(@D)

# C compiler mode. Future compilers may change the default on us,
# so force transition mode globally. Lower level makefiles can
# override this by setting CCMODE.
#
CCMODE=		-Xa
CCMODE64=	-Xa

# compiler '-xarch' flag. This is here to centralize it and make it
# overridable for testing.
sparc_XARCH=    $(CCBITS32) -xarch=sparc
sparcv9_XARCH=  $(CCBITS64) -xcode=abs64
i386_XARCH=     $(CCBITS32) -xchip=pentium
amd64_XARCH=    $(CCBITS64) -xarch=generic -Ui386 -U__i386

# disable the incremental linker
ILDOFF=         -xildoff

# C99 mode
C99_ENABLE=     -xc99=all
C99_DISABLE=    -xc99=none
C99MODE=        $(C99_ENABLE)
C99LMODE=       $(C99MODE:-xc99%=-Xc99%)

# XPG6 mode.  This option enables XPG6 conformance, plus extensions.
# Amongst other things, this option will cause system calls like
# popen (3C) and system (3C) to invoke the standards-conforming
# shell, /usr/xpg4/bin/sh, instead of /usr/bin/sh.
XPG6MODE=	$(C99MODE) -D_XOPEN_SOURCE=600 -D__EXTENSIONS__=1


# The Sun Studio 11 compiler has changed the behaviour of integer
# wrap arounds and so a flag is needed to use the legacy behaviour
# (without this flag panics/hangs could be exposed within the source).
#
sparc_IROPTFLAG		= -W2,-xwrap_int
sparcv9_IROPTFLAG	= -W2,-xwrap_int
i386_IROPTFLAG		=
amd64_IROPTFLAG		=
IROPTFLAG		= $($(MACH)_IROPTFLAG)
IROPTFLAG64		= $($(MACH64)_IROPTFLAG)

sparc_CFLAGS=	$(sparc_XARCH)
sparcv9_CFLAGS=	$(sparcv9_XARCH) -dalign $(CCVERBOSE)
i386_CFLAGS=	$(i386_XARCH)
amd64_CFLAGS=	$(amd64_XARCH)

sparc_COPTFLAG=		-xO3
sparcv9_COPTFLAG=	-xO3
i386_COPTFLAG=		-xO3
amd64_COPTFLAG=		-xO3
COPTFLAG= $($(MACH)_COPTFLAG)
COPTFLAG64= $($(MACH64)_COPTFLAG)

sparc_XREGSFLAG		= -xregs=no%appl
sparcv9_XREGSFLAG	= -xregs=no%appl
i386_XREGSFLAG		=
amd64_XREGSFLAG		=
XREGSFLAG		= $($(MACH)_XREGSFLAG)
XREGSFLAG64		= $($(MACH64)_XREGSFLAG)

CFLAGS=  \
	$(COPTFLAG) $($(MACH)_CFLAGS) $(CCMODE) \
	$(ILDOFF) $(C99MODE) $(IROPTFLAG)

CFLAGS64= \
	$(COPTFLAG64) $($(MACH64)_CFLAGS) $(CCMODE64) \
	$(ILDOFF) $(C99MODE) $(IROPTFLAG64)

# build with a non-executable stack by default.
# override this if necessary
LD_MAP_NOEXSTK="-M /usr/lib/ld/map.noexstk"
LD_OPTIONS+= $(LD_MAP_NOEXSTK)

# Environment variables and arguments passed into the build and install
# environment(s).  These are the initial settings.
COMPONENT_BUILD_ENV= \
    LD_OPTIONS=$(LD_OPTIONS)
COMPONENT_INSTALL_ENV= \
    LD_OPTIONS=$(LD_OPTIONS)

# Add any bit-specific settings
COMPONENT_BUILD_ENV += $(COMPONENT_BUILD_ENV.$(BITS))
COMPONENT_BUILD_ARGS += $(COMPONENT_BUILD_ARGS.$(BITS))
COMPONENT_INSTALL_ENV += $(COMPONENT_INSTALL_ENV.$(BITS))
COMPONENT_INSTALL_ARGS += $(COMPONENT_INSTALL_ARGS.$(BITS))
