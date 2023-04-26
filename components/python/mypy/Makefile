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
#   $WS_TOOLS/python-integrate-project mypy
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		mypy
HUMAN_VERSION =			1.2.0
COMPONENT_SUMMARY =		mypy - Optional static typing for Python
COMPONENT_PROJECT_URL =		http://www.mypy-lang.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/9a/d0/d96d26e7a6f5a2ed4add8c649f30bce26fc413f25a6ecc5d93ab22c270e1/mypy-1.2.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f70a40410d774ae23fcb4afbbeca652905a04de7948eaf0b1789c8d1426b72d1
COMPONENT_LICENSE =		MIT AND PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Testing needs to compile some C++ sources
COMPONENT_TEST_ENV += CXX="$(CXX)"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/mypy-extensions
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/typed-ast
PYTHON_REQUIRED_PACKAGES += library/python/types-psutil
PYTHON_REQUIRED_PACKAGES += library/python/types-setuptools
PYTHON_REQUIRED_PACKAGES += library/python/types-typed-ast
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/attrs
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/filelock
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/flake8-bugbear
TEST_REQUIRED_PACKAGES.python += library/python/flake8-noqa
TEST_REQUIRED_PACKAGES.python += library/python/isort
TEST_REQUIRED_PACKAGES.python += library/python/lxml
TEST_REQUIRED_PACKAGES.python += library/python/mypy-extensions
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/py
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-forked
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/six
TEST_REQUIRED_PACKAGES.python += library/python/tomli
TEST_REQUIRED_PACKAGES.python += library/python/typed-ast
TEST_REQUIRED_PACKAGES.python += library/python/types-psutil
TEST_REQUIRED_PACKAGES.python += library/python/types-setuptools
TEST_REQUIRED_PACKAGES.python += library/python/types-typed-ast
TEST_REQUIRED_PACKAGES.python += library/python/typing-extensions
