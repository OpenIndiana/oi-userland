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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		anyio
HUMAN_VERSION =			4.1.0
COMPONENT_SUMMARY =		anyio - High level compatibility layer for multiple asynchronous event loop implementations
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/6e/57/075e07fb01ae2b740289ec9daec670f60c06f62d04b23a68077fd5d73fab/anyio-4.1.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5a0bec7085176715be77df87fc66d6c9d70626bd752fcc85f57cdbee5b3760da
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# anyio --> anyio
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# We have no trio packaged yet.
# https://github.com/python-trio/trio/issues/1437
COMPONENT_POST_UNPACK_ACTION += $(RM) $(COMPONENT_SRC)/src/anyio/_backends/_trio.py ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/exceptiongroup
PYTHON_REQUIRED_PACKAGES += library/python/idna
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/sniffio
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/anyio
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/exceptiongroup
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/trustme
TEST_REQUIRED_PACKAGES.python += library/python/uvloop
