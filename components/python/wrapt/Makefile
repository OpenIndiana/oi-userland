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
# Copyright 2021 Gary Mills
#

BUILD_BITS = 64
BUILD_STYLE= setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		wrapt
COMPONENT_VERSION=	1.12.1
COMPONENT_FMRI=         library/python/wrapt
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_PROJECT_URL=	https://github.com/GrahamDumpleton/wrapt
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:19f2043e05b76ce9b68971b387bfd8eed50c2ee1c9c0bd230edc422fec753917
COMPONENT_ARCHIVE_URL= \
  https://github.com/GrahamDumpleton/$(COMPONENT_NAME)/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=      BSD

PYTHON_VERSIONS=	3.7 3.9

include $(WS_MAKE_RULES)/common.mk

COMPONENT_TEST_DIR =    $(SOURCE_DIR)/tests
COMPONENT_TEST_CMD =    $(PYTHON) -m pytest
COMPONENT_TEST_ARGS =

# Typical failures for test target:
#=========================== short test summary info ============================
#FAILED test_outer_classmethod.py::TestCallingOuterClassMethod::test_class_call_function
#FAILED test_outer_classmethod.py::TestCallingOuterClassMethod::test_instance_call_function
#FAILED test_synchronized_lock.py::TestSynchronized::test_synchronized_outer_classmethod
#================== 3 failed, 371 passed, 55 warnings in 1.47s ==================

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
REQUIRED_PACKAGES += system/library
