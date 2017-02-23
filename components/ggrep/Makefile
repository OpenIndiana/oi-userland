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
BUILD_BITS= 64
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		grep
COMPONENT_VERSION=	2.25
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:e21e83bac50450e0d0d61a42c154ee0dceaacdbf4f604ef6e79071cb8e596830
COMPONENT_BUGDB=	utility/ggrep
COMPONENT_ANITYA_ID=	1251

TPNO=			28105

SYSTEM_TEST_TARGET= $(SOURCE_DIR)/.system-test-patched configure $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

CONFIGURE_PREFIX   = $(USRGNUDIR)
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --localedir=$(USRSHARELOCALEDIR)

# Needed for "gmake test" to work.
# SHELLOPTS is exported via make-rules/shared-macros.mk,
# causing the braceexpand option to be set.
# This option causes "$1: unbound variable" errors during the check-TESTS,
# and the gnulib-tests don't even run at all.
# Note that the below unexports SHELLOPTS, even for targets
# other than "test." 
unexport SHELLOPTS

# Test transforms retain only relevant results output.
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL/p" ' \
        '-e "/SKIP/p" ' \
        '-e "/PASS/p" ' \
        '-e "/FAIL/p" ' \
        '-e "/ERROR/p" '

# Putting GNU on path first prevents some tests from being skipped,
# which also  keeps the test and system-test results consistent.
# With the test target, the path to the just-built commands is
# prepended to PATH.  With the system-test target, we patch
# to prevent the PATH from being prepended.
COMPONENT_TEST_ENV += "PATH=$(GNUBIN):$(PATH)"
COMPONENT_SYSTEM_TEST_ENV += "PATH=$(GNUBIN):$(PATH)"

# Patch to change test path so it tests grep commands from /usr/gnu/bin
# installed on the test system. If we patch, we must re-configure the
# tests.
$(SOURCE_DIR)/.system-test-patched: $(SOURCE_DIR)/.prep
	$(GPATCH) -d $(@D) $(GPATCH_FLAGS) < $(COMPONENT_DIR)/system-test-patches/systest.patch
	$(TOUCH) $(@)

# if we previously patched the source for the system-test target,
# ensure we rebuild without that patch
COMPONENT_PRE_TEST_ACTION += \
	if [ -e $(SOURCE_DIR)/.system-test-patched ]; then \
	   cd $(COMPONENT_DIR); \
	   $(GMAKE) clean build; \
	fi

REQUIRED_PACKAGES += developer/gcc
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += shell/bash
