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
#   $WS_TOOLS/python-integrate-project psutil
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		psutil
HUMAN_VERSION =			7.2.1
COMPONENT_SUMMARY =		Cross-platform lib for process and system monitoring.
COMPONENT_PROJECT_URL =		https://github.com/giampaolo/psutil
COMPONENT_ARCHIVE_HASH =	\
	sha256:f7583aec590485b43ca601dd9cea0dcd65bd7bb21d30ef4ddbf4ea6b5ed1bdd3
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

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
COMPONENT_PRE_TEST_ACTION +=	$(MV) $(@D)/psutil $(@D)/psutil-RENAMED ;
COMPONENT_POST_TEST_ACTION +=	$(MV) $(@D)/psutil-RENAMED $(@D)/psutil ;

# https://github.com/giampaolo/psutil/issues/2686
COMPONENT_TEST_ENV += PSUTIL_DEBUG=0

# fails on zfs
PYTEST_ADDOPTS += --deselect tests/test_posix.py::TestSystemAPIs::test_disk_usage
# process priority and nice does not match
PYTEST_ADDOPTS += --deselect tests/test_process.py::TestProcess::test_nice
# https://github.com/giampaolo/psutil/issues/2358
PYTEST_ADDOPTS += --deselect tests/test_process_all.py::TestFetchAllProcesses::test_all
# these tests are unable to find setup.py because we run tests from non-default directory
PYTEST_ADDOPTS += --deselect tests/test_scripts.py::TestSetupScript::test_invocation
PYTEST_ADDOPTS += --deselect tests/test_scripts.py::TestSetupScript::test_python2
# we have no pyperf packaged yet
PYTEST_ADDOPTS += --deselect tests/test_scripts.py::TestInternalScripts::test_import_all
# The test_memory_maps fails on Python 3.9 due to the not so robust realpath implementation
PYTEST_ADDOPTS += --deselect tests/test_unicode.py::TestFSAPIs::test_memory_maps
PYTEST_ADDOPTS += --deselect tests/test_unicode.py::TestFSAPIsWithInvalidPath::test_memory_maps

# We have no psleak packaged yet
PYTEST_ADDOPTS += --ignore tests/test_memleaks.py

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
