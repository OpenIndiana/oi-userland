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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#

BUILD_STYLE = setup.py
BUILD_BITS = NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		idna
COMPONENT_VERSION=	2.8
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c357b3f628cf53ae2c4c05627ecc484553142ca23264e593d327bcde5e9c3407
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/kjd/idna

PYTHON_VERSIONS=	2.7 3.5

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR = $(SOURCE_DIR)/tests
COMPONENT_TEST_ARGS = -m unittest discover --pattern=*.py

# The test output contains arbitrary output. Use nawk to extract just the
# sections that summarizes the test result.
# Most of the test cases skipped in Python 2.7 because 'Test requires Python 
# wide Unicode support'.
COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/^Ran .+ / { sub(\" tests in .+s\", \" tests in\"); print }; /!NF/ { print }; /^OK/ { print };'"

