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

BUILD_BITS=NO_ARCH
BUILD_STYLE=setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ipaddress
COMPONENT_VERSION=	1.0.23
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:12e953b1697999ddbfcba6abb558e646f6a4c5c11cacb57839469dce8bb8d1e4
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=  https://github.com/phihag/ipaddress
COMPONENT_BUGDB=	python-mod/ipaddress
COMPONENT_ANITYA_ID=	6374

# ipaddress is superfluous in Python 3.4
PYTHON_VERSIONS =	2.7

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR = $(SOURCE_DIR)
COMPONENT_TEST_ARGS = test_ipaddress.py
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(^Ran [0-9]\+ tests in\).*|\1|" '

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

