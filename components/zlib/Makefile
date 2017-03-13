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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 64_and_32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		zlib
COMPONENT_VERSION=	1.2.11
COMPONENT_PROJECT_URL=	http://www.zlib.net/
COMPONENT_ARCHIVE_HASH=	\
    sha256:c3e5e9fdd5004dcb542feda5ee4f0ff0744628baf8ed2dd5d66f8ca1197cb1a1
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/libpng/zlib/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libz
COMPONENT_ANITYA_ID=	5303

TPNO=			33488

# Omit directory options that cause zlib's CMake-based build to fail.
CONFIGURE_DEFAULT_DIRS=no
include $(WS_MAKE_RULES)/common.mk

#
# We want to build hardware specific versions of the longest_match()
# function into our shared library that has been hand optimised to use
# some machine architecture specific instructions. Currently, we are doing
# it for the T4 architecture, but later other architectures may be added.
# This is done by taking advantage of the Solaris 11 linker-editor
# "Symbol Capabilities" feature.  Refer to the section "Creating a Family
# of Symbol Capabilities Functions", under "Identifying Capability
# Requirements" in the "Linker and Libraries Guide"
# (http://docs.oracle.com/cd/E19963-01/html/819-0690/chapter2-13.html#giskh).
CAP_OBJS_sparcv7 += ../../capabilities/sun4v/sparcv7/symcap.o 
CAP_OBJS_sparcv9 += ../../capabilities/sun4v/sparcv9/symcap.o 
$(BUILD_DIR)/%/.built: CAP_OBJS=$(CAP_OBJS_$*)

# Zlib won't build without cloning. We need also to get rid of default
# Makefile and get our own version of zconf.h to avoid interactions
# between 32 and 64 bit builds.
# Also, the x86 architecture does not require alignment for multi-byte
# loads, so we can define UNALIGNED_OK for x86
ifeq ($(MACH), i386)
COMPONENT_PRE_CONFIGURE_ACTION = ( \
	$(CLONEY) $(SOURCE_DIR) $(@D); \
	$(RM) $(@D)/Makefile $(@D)/zconf.h; \
	$(CP) $(SOURCE_DIR)/zconf.h $(@D) )
CFLAGS_EXTRA = -DUNALIGNED_OK -DORIG_LONGEST_MATCH_GLOBAL
PIC_OBJA=
else
COMPONENT_PRE_CONFIGURE_ACTION = ( \
	$(CLONEY) $(SOURCE_DIR) $(@D); \
	$(RM) $(@D)/Makefile $(@D)/zconf.h; \
	$(CP) $(SOURCE_DIR)/zconf.h $(@D) )
CFLAGS_EXTRA = -DORIG_LONGEST_MATCH_GLOBAL -xinline=%auto,no%longest_match
PIC_OBJA=$(CAP_OBJS)
endif

# Avoid *.lo.bc from Parfait analyze (see also parfait.patch).
PARFAIT += -X *.lo.bc

CFLAGS += $(CC_PIC)

CFLAGS += $(CFLAGS_EXTRA)

# We need to reset configure options here because zlib is confused with
# CC and CFLAGS definitions as configure parameters.
CONFIGURE_OPTIONS	+= --shared
CONFIGURE_OPTIONS.64	+= --libdir=$(USRLIBDIR64)

CFLAGS.studio += -xalias_level=basic -xdepend

CONFIGURE_ENV += LDSHARED="$(CC) $(CFLAGS) -G"

# This LDSHARED definitions is forced to get all required options plus
# mapfile for result linking. While the one used with configure is just
# to allow Zlib detect capability of creating shared libraries.
COMPONENT_BUILD_ARGS = LDSHARED="$(CC) $(CFLAGS) -G -h libz.so.1 $(LD_OPTIONS_SO) -M ../../mapfile -L." PIC_OBJA=$(PIC_OBJA)

$(BUILD_DIR)/sparc%/.built: COMPONENT_PRE_BUILD_ACTION = ( \
	cd capabilities; \
	$(ENV) SUBDIRS="sun4v" BUILD_ARCH=$* CC=$(CC) $(GMAKE) build )

COMPONENT_TEST_TARGETS = test

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += '-e "/^zlib version/s/0x..$$/0xXX/" '

COMPONENT_SYSTEM_TEST_TARGETS= test SYSTEM_TEST=1

CLEAN_PATHS += $(PROTO_DIR) capabilities/*/*/*.o capabilities/*/*/*.s

system-test: build $(SYSTEM_TEST_32_and_64)

