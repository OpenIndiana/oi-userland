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
# Copyright 2017 Gary Mills
# Copyright 2017 Aurelien Larcher
# Copyright 2019 Michal Nowak
# Copyright 2020-2021 Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         coreutils
COMPONENT_VERSION=      9.2
COMPONENT_FMRI=         file/gnu-coreutils	
COMPONENT_SUMMARY=		GNU Core Utilities are the basic file, shell and text manipulation utilities
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/coreutils/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:6885ff47b9cdb211de47d368c17853f406daaf98b148aaecdf10de29cc04b0b3
COMPONENT_ARCHIVE_URL=  https://ftp.gnu.org/gnu/coreutils/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      GPLv3, FDLv1.3

include $(WS_MAKE_RULES)/common.mk

# We need the GNU grep command to configure/build.
PATH = $(PATH.gnu)

PATCH_LEVEL = 0

gcc_OPT.sparc.32 = -O1

# Recreate configure and Makefile to pick up changes in .../src/local.mk
COMPONENT_PREP_ACTION = (cd $(@D) ; autoreconf -f -i)

CONFIGURE_PREFIX	 =	$(GNUDIR)
CONFIGURE_BINDIR.64	 =	$(GNUBIN)
CONFIGURE_OPTIONS	+=	CPPFLAGS=" -I$(USRINCDIR)/gmp"
CONFIGURE_OPTIONS	+=	--libdir=$(USRLIBDIR.$(BITS))
# Put libstdbuf in the library directory
CONFIGURE_OPTIONS	+=	--libexecdir=$(USRLIBDIR.$(BITS))
CONFIGURE_OPTIONS	+=	--infodir=$(CONFIGURE_INFODIR)

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# OS as reported by `uname -o`
CONFIGURE_ENV		+=	gl_cv_host_operating_system=illumos

COMPONENT_POST_INSTALL_ACTION += ( cp $(COMPONENT_DIR)/files/*.1 \
                                      $(PROTOGNUSHAREMAN1) ) 

# Build 32-bit for libstdbuf only, then overwrite with 64bit binaries
build:		$(BUILD_32_and_64)

# Make sure 32-bit binaries are installed first
$(INSTALL_64): $(INSTALL_32)

install:	$(INSTALL_32_and_64)

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Get the binaries to test from the component proto area.
COMPONENT_TEST_ENV += PATH=$(PROTOGNUBIN):$(USRBINDIR)

# Always show the build and link lines for easier debugging.
# COMPONENT_TEST_ARGS +=	V=1
#

# Master test results are different between x86 and SPARC (different # of
# tests run).
COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-$(MACH).master

# Some tests pass or are skip depending on the host.
# Let us just check for failed tests.
COMPONENT_TEST_TRANSFORMS += \
 	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

test:		install $(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += system/library
