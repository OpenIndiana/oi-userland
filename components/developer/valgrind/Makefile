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
# Copyright (c) 2022,2023 Friedrich Kink
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		valgrind
COMPONENT_VERSION=	3.22.0
COMPONENT_FMRI=		developer/debug/valgrind
COMPONENT_CLASSIFICATION=Development/System
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:c811db5add2c5f729944caf47c4e7a65dcaabb9461e472b578765dd7bf6d2d4c
COMPONENT_ARCHIVE_URL=	https://sourceware.org/pub/valgrind/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL =	https://valgrind.org
COMPONENT_SUMMARY=	Valgrind: instrumentation framework and tools to detect memory and threading problems
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Use GNU utilities
PATH=$(PATH.gnu)

COMPONENT_PRE_CONFIGURE_ACTION = \
	( $(CLONEY) $(SOURCE_DIR) $(@D) )

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
CONFIGURE_OPTIONS += --enable-inner
CONFIGURE_OPTIONS += --enable-tls
CONFIGURE_OPTIONS += --with-mpicc=$(USRLIBDIR)/openmpi/gcc/bin/mpicc

COMPONENT_PREP_ACTION += ( cd $(@D) && ./autogen.sh )

# config.h is generated in the build directory while it is assumed to live in the source dir
COMPONENT_POST_CONFIGURE_ACTION += ( cp $(@D)/config.h $(SOURCE_DIR) )

COMPONENT_POST_BUILD_ACTION += \
	( cd $(@D)/docs && $(ENV) $(GMAKE) man-pages )

#
# currently 3.22.0
# == 835 tests, 62 stderr failures, 14 stdout failures, 0 stderrB failures, 0 stdoutB failures, 6 post failures ==
#
COMPONENT_TEST_TARGETS = regtest
# check just overal test results
COMPONENT_TEST_TRANSFORMS += '-n -e "/^== /p"'

# Build dependencies
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/gcc-13
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
