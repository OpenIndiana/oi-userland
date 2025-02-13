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
#   $WS_TOOLS/python-integrate-project redis
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		redis
HUMAN_VERSION =			5.2.1
COMPONENT_SUMMARY =		Python client for Redis database and key-value store
COMPONENT_PROJECT_URL =		https://github.com/redis/redis-py
COMPONENT_ARCHIVE_URL =		\
	https://github.com/redis/redis-py/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fdb92ef773faac88c2bf80c47ecddbbdf93bae93363b4e6f9418b5686260420b
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

COMPONENT_SRC =			redis-py-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += dev_requirements.txt

# To test we need database/redis installed and the
# svc:/application/database/redis:default service must be online
TEST_REQUIRED_PACKAGES += database/redis

# We do not run following sets of tests:
# - module tests since we do not have any Redis modules
# - cluster tests since we do not run Redis in cluster
# - ssl tests since our Redis is not built with TLS support
# - replica tests since we do not have replica Redis
PYTEST_ADDOPTS += -m "not redismod and not onlycluster and not ssl and not replica"
# We have no RedisBloom support
PYTEST_ADDOPTS += --ignore tests/test_bloom.py
PYTEST_ADDOPTS += --ignore tests/test_asyncio/test_bloom.py
# We have no RedisGraph support
PYTEST_ADDOPTS += --ignore tests/test_graph.py
PYTEST_ADDOPTS += --ignore tests/test_asyncio/test_graph.py
# We have no JSON support for Redis
PYTEST_ADDOPTS += --ignore tests/test_json.py
PYTEST_ADDOPTS += --ignore tests/test_asyncio/test_json.py
# We have no RedisTimeSeries support
PYTEST_ADDOPTS += --ignore tests/test_timeseries.py
PYTEST_ADDOPTS += --ignore tests/test_asyncio/test_timeseries.py

# https://github.com/redis/redis-py/issues/3508
PYTEST_ADDOPTS += --ignore tests/test_asyncio/test_cluster.py

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/async-timeout
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/click
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/invoke
TEST_REQUIRED_PACKAGES.python += library/python/mock
TEST_REQUIRED_PACKAGES.python += library/python/numpy
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-asyncio
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/wheel
