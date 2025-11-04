#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project regex
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		regex
HUMAN_VERSION =			2025.10.23
COMPONENT_SUMMARY =		Alternative regular expression module, to replace re.
COMPONENT_PROJECT_URL =		https://github.com/mrabarnett/mrab-regex
COMPONENT_ARCHIVE_HASH =	\
	sha256:8cbaf8ceb88f96ae2356d01b9adf5e6306fa42fa6f7eab6b97794e37c959ac26
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

#
# Tests are run from build directory that contains cloned copy of sdist.  We
# try to ask Python to find tested modules in the proto area (the PYTHONPATH is
# set accordingly), but Python (< 3.11) always adds the current directory to
# sys.path and there is no known (simple) way how to avoid that.  Except -I,
# but that would cause Python to ignore PYTHONPATH too so we would not have
# access to the proto area either.  The -P option together with PYTHONSAFEPATH
# environment variable were added to Python 3.11 only so we cannot use them yet
# for all Python versions we support.
#
# Since sdist for this project contains the main module in the top-level
# directory we cannot force Python to skip it.  But, unfortunately, this module
# does not contain built dynamic libraries, so Python cannot find them while
# testing.
#
# To workaround this we rename the main module in the build directory during
# testing so Python will need to defer to PYTHONPATH.
#
COMPONENT_PRE_TEST_ACTION +=	$(MV) $(@D)/regex $(@D)/regex-RENAMED ;
COMPONENT_POST_TEST_ACTION +=	$(MV) $(@D)/regex-RENAMED $(@D)/regex ;

# https://github.com/mrabarnett/mrab-regex/issues/448#issuecomment-2222396902
PYTEST_ADDOPTS += --deselect regex-RENAMED/tests/test_regex.py::test_main

# Remove extra -RENAMED from test report
COMPONENT_TEST_TRANSFORMS += "-e 's/\(regex\)-RENAMED/\1/g'"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
