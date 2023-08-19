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
# Copyright (c) 2013  Erol Zavidic. All rights reserved.
# Copyright (c) 2022  Tim Mooney.  All rights reserved.
#

BUILD_BITS=             32_and_64
USE_COMMON_TEST_MASTER= no
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         zlib
COMPONENT_VERSION=      1.3
COMPONENT_SUMMARY=      The Zip compression library
COMPONENT_PROJECT_URL=  https://zlib.net/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  https://zlib.net/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=      $(COMPONENT_ARCHIVE_URL).asc
COMPONENT_ARCHIVE_HASH=	sha256:ff0ba4c292013dbc27530b3a81e1f9a813cd39de01ca5e0f8bf355702efa593e
COMPONENT_FMRI=         library/zlib
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=      zlib license
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/common.mk


# Zlib won't build without cloning. We need also to get rid of default
# Makefile and get our own version of zconf.h to avoid interactions
# between 32 and 64 bit builds.
COMPONENT_PRE_CONFIGURE_ACTION = ( \
	$(CLONEY) $(SOURCE_DIR) $(@D); \
	$(RM) $(@D)/Makefile $(@D)/zconf.h; \
	$(CP) $(SOURCE_DIR)/zconf.h $(@D) )

# Also, the x86 architecture does not require alignment for multi-byte
# loads, so we can define UNALIGNED_OK for x86
CFLAGS.i386.32 += -DUNALIGNED_OK

CFLAGS += $(CC_PIC)
CFLAGS += $(CFLAGS.$(MACH).$(BITS))

# We need to reset configure options here because zlib is confused with
# CC and CFLAGS definitions as configure parameters.
# Note that this is NOT an autoconf-generated standard configure script.
CONFIGURE_OPTIONS	=  --shared
CONFIGURE_OPTIONS	+= --prefix=/usr
CONFIGURE_OPTIONS.32	=
CONFIGURE_OPTIONS.64	= --64
CONFIGURE_OPTIONS.64	+= --libdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS	+= $(CONFIGURE_OPTIONS.$(BITS))

CONFIGURE_ENV += LDSHARED="$(CC) $(CFLAGS) -G"

# This LDSHARED definitions is forced to get all required options plus
# mapfile for result linking. While the one used with configure is just
# to allow Zlib detect capability of creating shared libraries.
COMPONENT_BUILD_ARGS = LDSHARED="$(CC) $(CFLAGS) $(LDFLAGS) -shared -Wl,-z -Wl,text -Wl,-h -Wl,libz.so.1 $(LD_OPTIONS_SO) -Wl,-M -Wl,../../mapfile -L."

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
