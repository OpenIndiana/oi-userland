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
#   $WS_TOOLS/python-integrate-project -d python/anyio-39 anyio
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		anyio
HUMAN_VERSION =			4.12.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		High-level concurrency and networking framework on top of asyncio or Trio
COMPONENT_ARCHIVE_HASH =	\
	sha256:41cfcc3a4c85d3f05c932da7c26d0201ac36f72abd4435ba90d0464a3ffed703
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# anyio >= 4.13.0 requires Python >= 3.10
PYTHON_VERSIONS = 3.9

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
