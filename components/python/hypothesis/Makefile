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
# Copyright (c) 2019, Oracle and/or its affiliates. All rights reserved.
# Copyright 2021 Gary Mills
# Copyright 2022 Andreas Wacknitz
#

BUILD_STYLE = setup.py
BUILD_BITS = NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hypothesis
COMPONENT_VERSION=	4.57.1
COMPONENT_SUMMARY=	Hypothesis is an advanced testing library for Python
COMPONENT_DESCRIPTION=	Hypothesis is an advanced testing library for Python. \
						It lets you write tests which are parametrized by a source of examples, \
						and then generates simple and comprehensible examples that make your tests fail. \
						This lets you find more bugs in your code with less work.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:3c4369a4b0a1348561048bcda5f1db951a1b8e2a514ea8e8c70d36e656bf6fa0
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/HypothesisWorks/hypothesis
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_FMRI=	library/python/$(COMPONENT_NAME)
COMPONENT_LICENSE=	MPLv2

PYTHON_VERSIONS = 3.5 3.7 3.9

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
