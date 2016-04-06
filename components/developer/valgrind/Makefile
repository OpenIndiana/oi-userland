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
# Copyright (c) 2015 Aurelien Larcher. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		valgrind
COMPONENT_VERSION=	3.11.0
COMPONENT_REVISION=	1
COMPONENT_FMRI=	developer/debug/valgrind
COMPONENT_CLASSIFICATION=Development/System
COMPONENT_SRC=		iraisr-valgrind-solaris-9f9e059c22b3
COMPONENT_ARCHIVE=	r1508.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:6685a9eb81329fecc92aca5458af45c21ec418a5b5a2122a3141a691bf79691f
COMPONENT_ARCHIVE_URL=	https://bitbucket.org/iraisr/valgrind-solaris/get/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL =	https://bitbucket.org/iraisr/valgrind-solaris
COMPONENT_SUMMARY=	Valgrind: instrumentation framework and tools to detect memory and threading problems
COMPONENT_BUGDB=	developer/debug/valgrind
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Use GNU utilities
PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

# Force use of GCC with given arch support
CC=$(CC.gcc.$(BITS)) $(CC_BITS) -std=c99
CXX=$(CC.g++.$(BITS)) $(CC_BITS)

# Flags are inferred from CC
CFLAGS=
CXXFLAGS=
LDFLAGS=

CONFIGURE_DEFAULT_DIRS=no
CONFIGURE_OPTIONS += --mandir=$(CONFIGURE_MANDIR)
CONFIGURE_OPTIONS += --bindir=$(USRBINDIR$(BITS))
CONFIGURE_OPTIONS += --sbindir=$(USRSBINDIR$(BITS))
CONFIGURE_OPTIONS += --libdir=$(CONFIGURE_LIBDIR.$(BITS))

COMPONENT_PREP_ACTION+= (cd $(@D) && ./autogen.sh )

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
