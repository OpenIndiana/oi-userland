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
LAST_HG_TAG =	$(shell hg tags -q | grep build- | head -1)
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

CLONEY =	$(WS_TOOLS)/cloney

PKG_REPO =	file:$(WS_REPO)

COMPONENT_DIR =	$(shell pwd)
SOURCE_DIR =	$(COMPONENT_DIR)/$(COMPONENT_SRC)
BUILD_DIR =	$(COMPONENT_DIR)/build
PROTO_DIR =	$(BUILD_DIR)/prototype/$(MACH)

ETCDIR =	/etc
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
PROTOETCDIR =	$(PROTO_DIR)/$(ETCDIR)
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
SFWLIB64 =	/usr/sfw/lib/$(MACH64)
SFWSHARE =	/usr/sfw/share
SFWSHAREMAN =	/usr/sfw/share/man
SFWSHAREMAN1 =	/usr/sfw/share/man/man1
PROTOSFWBIN =	$(PROTO_DIR)/$(SFWBIN)
PROTOSFWLIB =	$(PROTO_DIR)/$(SFWLIB)
PROTOSFWLIB64 =	$(PROTO_DIR)/$(SFWLIB64)
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

TEST_32 =		$(BUILD_DIR_32)/.tested
TEST_64 =		$(BUILD_DIR_64)/.tested
TEST_32_and_64 =	$(TEST_32) $(TEST_64)

# BUILD_TOOLS is the root of all tools not normally installed on the system.
BUILD_TOOLS =	/ws/onnv-tools

SPRO_ROOT =	$(BUILD_TOOLS)/SUNWspro
SPRO_VROOT =	$(SPRO_ROOT)/sunstudio12.1

GCC_ROOT =	/usr/gnu

CC.studio.32 =	$(SPRO_VROOT)/bin/cc
CCC.studio.32 =	$(SPRO_VROOT)/bin/CC

CC.studio.64 =	$(SPRO_VROOT)/bin/cc
CCC.studio.64 =	$(SPRO_VROOT)/bin/CC

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

JAVA_HOME =	/usr/jdk/instances/jdk1.6.0

GMAKE =		/usr/gnu/bin/make
GPATCH =	/usr/gnu/bin/patch
PATCH_LEVEL =	1
GPATCH_BACKUP =	--backup --version-control=numbered
GPATCH_FLAGS =	-p$(PATCH_LEVEL) $(GPATCH_BACKUP)

PKGREPO =	/usr/bin/pkgrepo
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

#
# C preprocessor flag sets to ease feature selection.  Add the required
# feature to your Makefile with CPPFLAGS += $(FEATURE_MACRO) and add to
# the component build with CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)" or
# similiar.
#

# Enables visibility of some c99 math functions that aren't visible by default.
# What other side-effects are there?
CPP_C99_EXTENDED_MATH =	-D_STDC_99

# Enables large file support for components that have no other means of doing
# so.  Use CPP_LARGEFILES and not the .32/.64 variety directly
CPP_LARGEFILES.32 =	$(shell getconf LFS_CFLAGS)
CPP_LARGEFILES.64 =	$(shell getconf LFS64_CFLAGS)
CPP_LARGEFILES =		$(CPP_LARGEFILES.$(BITS))

# Enables some #pragma redefine_extname to POSIX-compliant Standard C Library
# functions. Also avoids the component's #define _POSIX_C_SOURCE to some value
# we currently do not support.
CPP_POSIX =	-D_POSIX_C_SOURCE=200112L -D_POSIX_PTHREAD_SEMANTICS

# XPG6 mode.  This option enables XPG6 conformance, plus extensions.
# Amongst other things, this option will cause system calls like
# popen (3C) and system (3C) to invoke the standards-conforming
# shell, /usr/xpg4/bin/sh, instead of /usr/bin/sh.  Add studio_XPG6MODE to
# CFLAGS instead of using this directly
CPP_XPG6MODE=	-D_XOPEN_SOURCE=600 -D__EXTENSIONS__=1 -D_XPG6


#
# Studio C compiler flag sets to ease feature selection.  Add the required
# feature to your Makefile with CFLAGS += $(FEATURE_MACRO) and add to the
# component build with CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)" or similiar.
#

# Generate 32/64 bit objects
CC_BITS =	-m$(BITS)

# Code generation instruction set and optimization 'hints'.  Use studio_XBITS
# and not the .arch.bits variety directly.
studio_XBITS.sparc.32 =	-xtarget=ultra2 -xarch=sparcvis -xchip=ultra2
studio_XBITS.sparc.64 =	-xtarget=ultra2 -xarch=sparcvis -xchip=ultra2
studio_XBITS.i386.32 =	-xchip=pentium
studio_XBITS.i386.64 =	-xchip=generic -Ui386 -U__i386
studio_XBITS = $(studio_XBITS.$(MACH).$(BITS))

# Turn on recognition of supported C99 language features and enable the 1999 C
# standard library semantics of routines that appear in	both the 1990 and
# 1999 C standard. To use set studio_C99MODE=$(studio_99_ENABLE) in your
# component Makefile.
studio_C99_ENABLE =		-xc99=all

# Turn off recognition of C99 language features, and do not enable the 1999 C
# standard library semantics of routines that appeared in both the 1990	and
# 1999 C standard.  To use set studio_C99MODE=$(studio_99_DISABLE) in your
# component Makefile.
studio_C99_DISABLE =	-xc99=none

# Use the compiler default 'xc99=all,no_lib'
studio_C99MODE =

# Allow zero-sized struct/union declarations and void functions with return
# statements.
studio_FEATURES_EXTENSIONS =	-features=extensions

# Control the Studio optimization level.
studio_OPT.sparc.32 =	-xO4
studio_OPT.sparc.64 =	-xO4
studio_OPT.i386.32 =	-xO4
studio_OPT.i386.64 =	-xO4
studio_OPT =		$(studio_OPT.$(MACH).$(BITS))

# Studio PIC code generation.  Use CC_PIC instead to select PIC code generation.
studio_PIC = 	-KPIC -DPIC

# The Sun Studio 11 compiler has changed the behaviour of integer
# wrap arounds and so a flag is needed to use the legacy behaviour
# (without this flag panics/hangs could be exposed within the source).
# This is used through studio_IROPTS, not the 'sparc' variety.
studio_IROPTS.sparc =	-W2,-xwrap_int
studio_IROPTS =		$(studio_IROPTS.$(MACH))

# Control register usage for generated code.  SPARC ABI requires system
# libraries not to use application registers.  x86 requires 'no%frameptr' at
# x04 or higher.
studio_XREGS.sparc =	-xregs=no%appl,float
studio_XREGS.i386 =	-xregs=no%frameptr
studio_XREGS =		$(studio_XREGS.$(MACH))

# Set data alignment on sparc to reasonable values, 8 byte alignment for 32 bit
# objects and 16 byte alignment for 64 bit objects.  This is added to CFLAGS by
# default.
studio_ALIGN.sparc.32 =	-xmemalign=8s
studio_ALIGN.sparc.64 =	-xmemalign=16s
studio_ALIGN =		$(studio_ALIGN.$(MACH).$(BITS))

# Studio shorthand for building multi-threaded code,  enables -D_REENTRANT and
# linking with threadin support.  This is added to CFLAGS by default, override
# studio_MT to turn this off.
studio_MT =		-mt

# See CPP_XPG6MODE comment above.
studio_XPG6MODE =	$(studio_C99MODE) $(CPP_XPG6MODE)
XPG6MODE =		$(studio_XPG6MODE)

# Default Studio C compiler flags.  Add the required feature to your Makefile
# with CFLAGS += $(FEATURE_MACRO) and add to the component build with
# CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)" or similiar.  In most cases, it
# should not be necessary to add CFLAGS to any environment other than the
# configure environment.
CFLAGS.studio +=	$(studio_OPT) $(studio_XBITS) $(studio_XREGS) \
			$(studio_IROPTS) $(studio_C99MODE) $(studio_ALIGN) \
			$(studio_MT)

#
# GNU C compiler flag sets to ease feature selection.  Add the required
# feature to your Makefile with CFLAGS += $(FEATURE_MACRO) and add to the
# component build with CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)" or similiar.
#

# GCC Compiler optimization flag
gcc_OPT =	-O3

# GCC PIC code generation.  Use CC_PIC instead to select PIC code generation.
gcc_PIC =	-fPIC -DPIC

# Generic macro for PIC code generation.  Use this macro instead of the
# compiler specific variant.
CC_PIC =	$($(COMPILER)_PIC)


# Default GNU C compiler flags.  Add the required feature to your Makefile
# with CFLAGS += $(FEATURE_MACRO) and add to the component build with
# CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)" or similiar.  In most cases, it
# should not be necessary to add CFLAGS to any environment other than the
# configure environment.
CFLAGS.gcc +=	$(gcc_OPT)


# Build 32 or 64 bit objects.
CFLAGS +=	$(CC_BITS)

# Add compiler specific 'default' features
CFLAGS +=	$(CFLAGS.$(COMPILER))


#
# Solaris linker flag sets to ease feature selection.  Add the required
# feature to your Makefile with LDFLAGS += $(FEATURE_MACRO) and add to the
# component build with CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)" or similiar.
#

# Reduce the symbol table size, effectively conflicting with -g.  We should
# get linker guidance here.
LD_Z_REDLOCSYM =	-z redlocsym

# Cause the linker to rescan archive libraries and resolve remaining unresolved
# symbols recursively until all symbols are resolved.  Components should be
# linking in the libraries they need, in the required order.  This should
# only be required if the component's native build is horribly broken.
LD_Z_RESCAN_NOW =	-z rescan-now

LD_Z_TEXT =		-z direct

# make sure all symbols are defined.
LD_Z_DEFS =		-z defs

# use direct binding
LD_B_DIRECT =		-Bdirect

#
# More Solaris linker flags that we want to be sure that everyone gets.  This
# is automatically added to the calling environment during the 'build' and
# 'install' phases of the component build.  Each individual feature can be
# turned off by adding FEATURE_MACRO= to the component Makefile.
#

# Create a non-executable stack when linking.
LD_MAP_NOEXSTK =	-M /usr/lib/ld/map.noexstk

# Create a non-executable bss segment when linking.
LD_MAP_NOEXBSS =	-M /usr/lib/ld/map.noexbss

# Create a non-executable data segment when linking.  Due to PLT needs, the
# data segment must be executable on sparc, but the bss does not.
# see mapfile comments for more information
LD_MAP_NOEXDATA.i386 =	-M /usr/lib/ld/map.noexdata
LD_MAP_NOEXDATA.sparc =	$(LD_MAP_NOEXBSS)

# Page alignment
LD_MAP_PAGEALIGN =	-M /usr/lib/ld/map.pagealign

# Linker options to add when only building libraries
LD_OPTIONS_SO +=	$(LD_Z_TEXT) $(LD_Z_DEFS)

# Default linker options that everyone should get.  Do not add additional
# libraries to this macro, as it will apply to everything linked during the
# component build.
LD_OPTIONS +=	$(LD_MAP_NOEXSTK) $(LD_MAP_NOEXDATA.$(MACH)) \
		$(LD_MAP_PAGEALIGN) $(LD_B_DIRECT)

# Environment variables and arguments passed into the build and install
# environment(s).  These are the initial settings.
COMPONENT_BUILD_ENV= \
    LD_OPTIONS="$(LD_OPTIONS)"
COMPONENT_INSTALL_ENV= \
    LD_OPTIONS="$(LD_OPTIONS)"

# Add any bit-specific settings
COMPONENT_BUILD_ENV += $(COMPONENT_BUILD_ENV.$(BITS))
COMPONENT_BUILD_ARGS += $(COMPONENT_BUILD_ARGS.$(BITS))
COMPONENT_INSTALL_ENV += $(COMPONENT_INSTALL_ENV.$(BITS))
COMPONENT_INSTALL_ARGS += $(COMPONENT_INSTALL_ARGS.$(BITS))
