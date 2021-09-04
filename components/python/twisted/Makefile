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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
#

BUILD_STYLE=setup.py
BUILD_BITS=32_and_64
PYTHON3_ONLY=yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         Twisted
COMPONENT_VERSION=      21.2.0
COMPONENT_FMRI=         library/python/python-twisted
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SUMMARY=      'Event-based framework for internet applications'
COMPONENT_PROJECT_URL=  http://twistedmatrix.com/trac/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:15cff97b63a244e14170d3caaeebd61a3d141fa5c9a97f229127f0d583543960
COMPONENT_ARCHIVE_URL=  $(call pypi_url)
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= twisted.license

include $(WS_MAKE_RULES)/common.mk

COMPONENT_POST_INSTALL_ACTION += ( cd $(PROTO_DIR)/usr/bin && \
	for file in cftp ckeygen conch mailmail pyhtmlizer tkconch trial twist twistd; \
	do mv $$file $$file-$(PYTHON_VERSION); done)

COMPONENT_TEST_DIR =	$(SOURCE_DIR)/src/twisted/test
COMPONENT_TEST_CMD =	$(PYTHON) -m pytest
COMPONENT_TEST_ARGS =	--verbose

# Unfortunately the master test results files are different for each version of Python.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(PYTHON_VERSION)-$(BITS).master

# The testsuite hangs at the end...
# 3.5:  12 failed, 2014 passed, 94 skipped, 49 warnings, 1 error
# 3.7:  8 failed, 1887 passed, 225 skipped, 37 warnings, 1 error
# 3.9:  8 failed, 1887 passed, 225 skipped, 39 warnings, 1 error
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/, [0-9]* warnings//" ' \
	'-n -e "s/in .* seconds //p"' \
	'-e "/::.*FAILED/p"' \
	'-e "/::.*ERROR/p"'


ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# Test dependency
REQUIRED_PACKAGES += library/python/automat-35
REQUIRED_PACKAGES += library/python/automat-37
REQUIRED_PACKAGES += library/python/automat-39
REQUIRED_PACKAGES += library/python/constantly-35
REQUIRED_PACKAGES += library/python/constantly-37
REQUIRED_PACKAGES += library/python/constantly-39
REQUIRED_PACKAGES += library/python/incremental-35
REQUIRED_PACKAGES += library/python/incremental-37
REQUIRED_PACKAGES += library/python/incremental-39
REQUIRED_PACKAGES += library/python/python-hamcrest-35
REQUIRED_PACKAGES += library/python/python-hamcrest-37
REQUIRED_PACKAGES += library/python/python-hamcrest-39

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += library/python/setuptools-37
REQUIRED_PACKAGES += library/python/setuptools-39
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39
