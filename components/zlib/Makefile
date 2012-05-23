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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		zlib
COMPONENT_VERSION=	1.2.3
COMPONENT_PROJECT_URL=	http://www.zlib.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1795c7d067a43174113fdf03447532f373e1c6c57c08d61d9e4e9be5e244b05e
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/libpng/zlib/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk
include ../../make-rules/lint-libraries.mk

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
PIC_OBJS =
else
COMPONENT_PRE_CONFIGURE_ACTION = ( \
	$(CLONEY) $(SOURCE_DIR) $(@D); \
	$(RM) $(@D)/Makefile $(@D)/zconf.h; \
	$(CP) $(SOURCE_DIR)/zconf.h $(@D) )
CFLAGS_EXTRA = -DORIG_LONGEST_MATCH_GLOBAL -xinline=%auto,no%longest_match
PIC_OBJS=$(CAP_OBJS)
endif

CFLAGS += $(CC_PIC)

CFLAGS += $(CFLAGS_EXTRA)

# We need to reset configure options here because zlib is confused with
# CC and CFLAGS definitions as configure parameters.
CONFIGURE_OPTIONS	=  --shared
CONFIGURE_OPTIONS	+= --prefix=/usr
CONFIGURE_OPTIONS	+= $(CONFIGURE_OPTIONS.$(BITS))
CONFIGURE_OPTIONS.64	+= --libdir=/usr/lib/$(MACH64)

CONFIGURE_ENV += CC="$(CC)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS) -xalias_level=basic -xdepend"
CONFIGURE_ENV += LDSHARED="$(CC) $(CFLAGS) -G"

# This LDSHARED definitions is forced to get all required options plus
# mapfile for result linking. While the one used with configure is just
# to allow Zlib detect capability of creating shared libraries.
COMPONENT_BUILD_ARGS = LDSHARED="$(CC) $(CFLAGS) -G -h libz.so.1 $(LD_OPTIONS_SO) -M ../../mapfile -L." PIC_OBJS=$(PIC_OBJS)

$(BUILD_DIR)/sparc%/.built: COMPONENT_PRE_BUILD_ACTION = ( \
	cd capabilities; \
	$(ENV) SUBDIRS="sun4v" BUILD_ARCH=$* $(GMAKE) build )

COMPONENT_TEST_TARGETS = test

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

clean::
	$(RM) -r $(BUILD_DIR) $(PROTO_DIR) capabilities/*/*/*.o

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
