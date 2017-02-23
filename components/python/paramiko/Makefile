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
# Copyright (c) 2012, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		paramiko
COMPONENT_VERSION=	2.0.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:411bf90fa22b078a923ff19ef9772c1115a0953702db93549a2848acefd141dc
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_PROJECT_URL=	http://github.com/paramiko/paramiko/
COMPONENT_BUGDB=	python-mod/paramiko
COMPONENT_ANITYA_ID=	3954

TPNO=			31171

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Master test results are the same for all versions of Python, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

# set LC_ALL for unicode sftp tests test_K_utf8 and test_L_utf8_chdir
COMPONENT_TEST_ENV=	LC_ALL=en_US.UTF-8 PYTHONPATH=$(SOURCE_DIR)
COMPONENT_TEST_DIR=	$(SOURCE_DIR)
COMPONENT_TEST_CMD=	$(PYTHON)
COMPONENT_TEST_ARGS=	test.py --verbose

# ============== is followed by hard-to-match tracebacks
COMPONENT_TEST_TRANSFORMS += \
    '-e "s/\<[.0-9]\+s\>/Xs/g"' \
    '-e "/==============/q"'

COMPONENT_SYSTEM_TEST_ENV=	LC_ALL=en_US.UTF-8
COMPONENT_SYSTEM_TEST_DIR=	$(SOURCE_DIR)
COMPONENT_SYSTEM_TEST_CMD=	$(PYTHON)
COMPONENT_SYSTEM_TEST_ARGS=	test.py --verbose

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(TEST_NO_ARCH)

system-test:	$(SYSTEM_TEST_NO_ARCH)

# locale required for unicode sftp tests
REQUIRED_PACKAGES += system/locale
