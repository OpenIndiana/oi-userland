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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		psutil
HUMAN_VERSION =			7.1.3
COMPONENT_SUMMARY =		Cross-platform lib for process and system monitoring.
COMPONENT_PROJECT_URL =		https://github.com/giampaolo/psutil
COMPONENT_ARCHIVE_HASH =	\
	sha256:6c86281738d77335af7aec228328e944b30930899ea760ecf33a4dba66be5e74
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += test

# We need to run tests in proto area to get access to compiled modules
COMPONENT_TEST_DIR = $(PROTO_DIR)/$(PYTHON_LIB)
# ... and so we need to point back to build dir for scripts subdirectory
COMPONENT_TEST_ENV += PSUTIL_ROOT_DIR=$(@D)
# https://github.com/giampaolo/psutil/issues/2686
COMPONENT_TEST_ENV += PSUTIL_DEBUG=0

# fails on zfs
PYTEST_ADDOPTS += --deselect psutil/tests/test_posix.py::TestSystemAPIs::test_disk_usage
# process priority and nice does not match
PYTEST_ADDOPTS += --deselect psutil/tests/test_process.py::TestProcess::test_nice
# https://github.com/giampaolo/psutil/issues/2358
PYTEST_ADDOPTS += --deselect psutil/tests/test_process_all.py::TestFetchAllProcesses::test_all
# these tests are unable to find setup.py because we run tests from non-default directory
PYTEST_ADDOPTS += --deselect psutil/tests/test_scripts.py::TestSetupScript::test_invocation
PYTEST_ADDOPTS += --deselect psutil/tests/test_scripts.py::TestSetupScript::test_python2
# we have no pyperf packaged yet
PYTEST_ADDOPTS += --deselect psutil/tests/test_scripts.py::TestInternalScripts::test_import_all
# The test_memory_maps fails on Python 3.9 due to the not so robust realpath implementation
PYTEST_ADDOPTS += --deselect psutil/tests/test_unicode.py::TestFSAPIs::test_memory_maps
PYTEST_ADDOPTS += --deselect psutil/tests/test_unicode.py::TestFSAPIsWithInvalidPath::test_memory_maps

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-subtests
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
