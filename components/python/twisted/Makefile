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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Twisted
COMPONENT_VERSION=	10.1.0
COMPONENT_PROJECT_URL=	http://twistedmatrix.com/trac/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
    sha256:eda6e0e9e5ef6f6c19ab75bcb094f83a12ee25fe589fbcddf946e8a655c8070b
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_BUGDB=	python-mod/twisted
COMPONENT_ANITYA_ID=	4071

TPNO=			9692

# Syntax issues: not Python 3 ready.
PYTHON_VERSIONS=	$(PYTHON2_VERSIONS)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_TEST_DIR= $(COMPONENT_SRC) 
COMPONENT_TEST_CMD= $(@D)/scripts-$(PYTHON_VERSION)/trial twisted
COMPONENT_TEST_ARGS=""

# Unfortunately the master test results files are not only different for
# each version of Python, they can also be different for 32-bit and 64-bit
# versions and different for x86 and SPARC platforms.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(PYTHON_VERSION)-$(BITS).$(MACH).master

# Using gsed with a specific set of transforms to be applied to the test
# results to try to normalize them, was problematic. It resulted in 8
# different ~650Kb master test files. Several of these lines needed to be
# deleted (as opposed to being normalized) because they appear in a
# non-deterministic order.
#
# Using nawk to just extract lines starting with:
# [FAIL]: ...
# [ERROR]: ...
# Ran XXXX tests in ...
# FAILED ...
# OK
# and stripping out the random portions (like time to complete the tests),
# resulted in 8 master test files each less than 1Kb in size.
COMPONENT_TEST_TRANSFORMER =    $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/^\[FAIL\]: / { print }; /^\[ERROR\]: / { print }; /^Ran / { sub(\" tests in .+s\", \" tests in\"); print }; /^FAILED / { print }; /^OK / { print };'"

COMPONENT_SYSTEM_TEST_DIR=	$(COMPONENT_SRC)
COMPONENT_SYSTEM_TEST_ENV=
COMPONENT_SYSTEM_TEST_CMD=	/usr/demo/twisted-python$(PYTHON_VERSION)/trial
COMPONENT_SYSTEM_TEST_ARGS=	twisted

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TEST_32_and_64)

REQUIRED_PACKAGES += system/library
