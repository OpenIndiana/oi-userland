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
#   $WS_TOOLS/python-integrate-project anyio
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		anyio
HUMAN_VERSION =			4.12.0
COMPONENT_SUMMARY =		High-level concurrency and networking framework on top of asyncio or Trio
COMPONENT_ARCHIVE_HASH =	\
	sha256:73c693b567b0c55130c104d0b43a9baf3aa6a31fc6110116509f27bf75e21ec0
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# We have no trio packaged yet.
# https://github.com/python-trio/trio/issues/1437
COMPONENT_POST_UNPACK_ACTION += $(RM) $(COMPONENT_SRC)/src/anyio/_backends/_trio.py ;

# https://github.com/agronholm/anyio/issues/986
PYTEST_ADDOPTS += --deselect tests/test_sockets.py::TestTCPStream::test_unretrieved_future_exception_server_crash

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/exceptiongroup
REQUIRED_PACKAGES.python += library/python/idna
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += library/python/typing-extensions
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/exceptiongroup
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/trustme
