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
#   $WS_TOOLS/python-integrate-project -d python/jaraco.mongodb jaraco_mongodb
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jaraco_mongodb
HUMAN_VERSION =			12.4.0
COMPONENT_SUMMARY =		Routines and classes supporting MongoDB environments
COMPONENT_ARCHIVE_HASH =	\
	sha256:dbd6908716d5c392258db97c5fad6097209ee5f93d70f469b0ecb91a177f67b5
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# We have no MongoDB packaged
PYTEST_ADDOPTS += --deselect tests/test_compat.py::test_save_no_id
PYTEST_ADDOPTS += --deselect tests/test_compat.py::test_save_new_with_id
PYTEST_ADDOPTS += --deselect tests/test_compat.py::test_save_replace_by_id
PYTEST_ADDOPTS += --deselect tests/test_compat.py::test_save_no_id_extant_docs
PYTEST_ADDOPTS += --deselect tests/test_compat.py::test_save_adds_id
PYTEST_ADDOPTS += --deselect tests/test_fields.py::test_insert_with_dots
PYTEST_ADDOPTS += --deselect tests/test_insert_doc.py::test_insert_doc_command
PYTEST_ADDOPTS += --deselect tests/test_manage.py::test_purge_all_databases
PYTEST_ADDOPTS += --deselect tests/test_service.py::test_fixture
PYTEST_ADDOPTS += --deselect tests/test_sessions.py::TestSessions::test_session_persists
PYTEST_ADDOPTS += --deselect tests/test_sessions.py::TestSessions::test_locked_session
PYTEST_ADDOPTS += --deselect tests/test_testing.py::test_assert_covered_passes
PYTEST_ADDOPTS += --deselect tests/test_testing.py::test_assert_covered_empty
PYTEST_ADDOPTS += --deselect tests/test_testing.py::test_assert_covered_null
PYTEST_ADDOPTS += --deselect tests/test_testing.py::test_assert_index_used_passes
PYTEST_ADDOPTS += --deselect tests/test_testing.py::test_assert_index_used_fails
PYTEST_ADDOPTS += --deselect jaraco/mongodb/helper.py::jaraco.mongodb.helper.server_version
PYTEST_ADDOPTS += --deselect jaraco/mongodb/query.py::jaraco.mongodb.query.upsert_and_fetch
PYTEST_ADDOPTS += --deselect jaraco/mongodb/sampling.py::jaraco.mongodb.sampling.estimate

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/backports-tarfile
PYTHON_REQUIRED_PACKAGES += library/python/cachetools
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-collections
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-context
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-functools
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-itertools
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-logging
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-services
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-ui
PYTHON_REQUIRED_PACKAGES += library/python/more-itertools
PYTHON_REQUIRED_PACKAGES += library/python/portend
PYTHON_REQUIRED_PACKAGES += library/python/pymongo
PYTHON_REQUIRED_PACKAGES += library/python/python-dateutil
PYTHON_REQUIRED_PACKAGES += library/python/pytimeparse
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/tempora
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/cherrypy
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
