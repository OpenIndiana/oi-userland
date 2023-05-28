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
#   $WS_TOOLS/python-integrate-project pyzmq
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyzmq
HUMAN_VERSION =			25.1.0
COMPONENT_SUMMARY =		pyzmq - Python bindings for 0MQ
COMPONENT_PROJECT_URL =		https://pyzmq.readthedocs.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/64/9c/2b2614b0b86ff703b3a33ea5e044923bd7d100adc8c829d579a9b71ea9e7/pyzmq-25.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:80c41023465d36280e801564a69cbfce8ae85ff79b080e1913f6e90481fb8957
COMPONENT_LICENSE =		BSD-3-Clause AND GPL-3.0-only

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += test-requirements.txt

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
# testing so Python will need to defer to PYTHONPATH.  We also need to preserve
# the tests subdirectory reachable via the original path because pytest.ini
# refers to it.
#
COMPONENT_PRE_TEST_ACTION +=	$(MV) $(@D)/zmq $(@D)/zmq-RENAMED ;
COMPONENT_PRE_TEST_ACTION +=	$(MKDIR) $(@D)/zmq ;
COMPONENT_PRE_TEST_ACTION +=	$(SYMLINK) ../zmq-RENAMED/tests $(@D)/zmq/tests ;
COMPONENT_POST_TEST_ACTION +=	$(RM) -r $(@D)/zmq ;
COMPONENT_POST_TEST_ACTION +=	$(MV) $(@D)/zmq-RENAMED $(@D)/zmq ;

# Testing fails with the checkdocs plugin installed
PYTEST_ADDOPTS += -p no:checkdocs
# Testing fails with the randomly plugin installed
PYTEST_ADDOPTS += -p no:randomly

# Testing of pyzmq fails if there is flaky installed.  See
# https://github.com/zeromq/pyzmq/issues/1802 for details.
TEST_CONFLICTING_PACKAGES.python += library/python/flaky

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cython
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/c++/zeromq
REQUIRED_PACKAGES += system/library
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/codecov
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/cython
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/gevent
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pymongo
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-asyncio
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-rerunfailures
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/tornado
