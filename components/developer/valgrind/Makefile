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
# Copyright (c) 2015-2017 Aurelien Larcher. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		valgrind
COMPONENT_VERSION=	3.13.0
COMPONENT_FMRI=	developer/debug/valgrind
COMPONENT_CLASSIFICATION=Development/System
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
  sha256:d76680ef03f00cd5e970bbdcd4e57fb1f6df7d2e2c071635ef2be74790190c3b
COMPONENT_ARCHIVE_URL=	ftp://sourceware.org/pub/valgrind/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL =	http://valgrind.org
COMPONENT_SUMMARY=	Valgrind: instrumentation framework and tools to detect memory and threading problems
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Use GNU utilities
PATH=$(PATH.gnu)

# Force use of GCC with given arch support
CC=$(CC.gcc.$(BITS)) $(CC_BITS) -std=gnu99
CXX=$(CC.g++.$(BITS)) $(CC_BITS)

# Flags are inferred from CC and tests rely on sigaction
CFLAGS= -D__EXTENSIONS__
CXXFLAGS= -D__EXTENSIONS__
LDFLAGS=

CONFIGURE_DEFAULT_DIRS=no
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --bindir=$(USRBINDIR)
CONFIGURE_OPTIONS += --sbindir=$(USRSBINDIR)
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))

COMPONENT_PREP_ACTION+= (cd $(@D) && ./autogen.sh )

# config.h is generated in the build directory while it is assumed to live in the source dir
COMPONENT_POST_CONFIGURE_ACTION+= (cp $(@D)/config.h $(SOURCE_DIR) )

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Build dependencies
REQUIRED_PACKAGES += runtime/perl-522

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
