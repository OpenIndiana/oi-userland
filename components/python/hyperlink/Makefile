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
# Copyright (c) 2021, Andreas Wacknitz
#

BUILD_STYLE = setup.py
BUILD_BITS = NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		hyperlink
COMPONENT_VERSION=	21.0.0
COMPONENT_SUMMARY=	'A featureful, immutable, and correct URL for Python'
COMPONENT_DESCRIPTION=	'Hyperlink provides a pure-Python implementation of immutable URLs. Based on RFC 3986 and 3987, the Hyperlink URL makes working with both URIs and IRIs easy'
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:427af957daa58bc909471c6c40f74c5450fa123dd093fc53efd2e91d2705a56b
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	https://github.com/python-hyper/hyperlink
COMPONENT_FMRI= library/python/hyperlink
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_LICENSE= MIT

PYTHON_VERSIONS = $(PYTHON3_VERSIONS)

include $(WS_MAKE_RULES)/common.mk

#COMPONENT_TEST_DIR =	$(SOURCE_DIR)
#COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
#COMPONENT_TEST_ARGS =

COMPONENT_TEST_DIR =	$(SOURCE_DIR)/src/twisted/test
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =	--verbose

# Unfortunately the master test results files are not only different for
# each version of Python, they can also be different for 32-bit and 64-bit
# versions and different for x86 and SPARC platforms.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(PYTHON_VERSION).master

COMPONENT_TEST_TRANSFORMS += \
	'-e "s/, [0-9]* warnings//" ' \
	'-n -e "s/in .* seconds //p"' \
	'-e "/::.*FAILED/p"' \
	'-e "/::.*ERROR/p"'

# testing dependencies
REQUIRED_PACKAGES += library/python/idna

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
