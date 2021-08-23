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
# Copyright (c) 2019 Michal Nowak
# Copyright (c) 2021 David Stes
#

BUILD_BITS= 64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		valgrind
COMPONENT_VERSION=	3.17.0
COMPONENT_REVISION=	1
COMPONENT_FMRI=		developer/debug/valgrind
COMPONENT_CLASSIFICATION=Development/System
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:ad3aec668e813e40f238995f60796d9590eee64a16dff88421430630e69285a2
COMPONENT_ARCHIVE_URL=	ftp://sourceware.org/pub/valgrind/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL =	http://valgrind.org
COMPONENT_SUMMARY=	Valgrind: instrumentation framework and tools to detect memory and threading problems
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

# Use GNU utilities
PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION = \
	( $(CLONEY) $(SOURCE_DIR) $(@D) )

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
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))

COMPONENT_PREP_ACTION += ( cd $(@D) && ./autogen.sh )

# config.h is generated in the build directory while it is assumed to live in the source dir
COMPONENT_POST_CONFIGURE_ACTION += ( cp $(@D)/config.h $(SOURCE_DIR) )

COMPONENT_POST_BUILD_ACTION += \
	( cd $(@D)/docs && $(ENV) $(GMAKE) man-pages )

#
# currently 3.17.0
# == 787 tests, 95 stderr failures, 18 stdout failures, 3 stderrB failures, 6 stdoutB failures, 7 post failures ==
#
COMPONENT_TEST_TARGETS = regtest
# check just overal test results
COMPONENT_TEST_TRANSFORMS += '-n -e "/^== /p"'

# Build dependencies
# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
