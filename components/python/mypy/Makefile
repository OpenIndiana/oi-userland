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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		mypy
HUMAN_VERSION =			1.11.1
COMPONENT_SUMMARY =		Optional static typing for Python
COMPONENT_PROJECT_URL =		https://www.mypy-lang.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:f404a0b069709f18bbdb702eb3dcfe51910602995de00bd39cea3050b5772d08
COMPONENT_LICENSE =		MIT AND PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Testing expects GNU make
PATH = $(PATH.gnu)

# Testing fails with strange errors when pytest-cov is enabled.
# This needs to be investigated further.
PYTEST_ADDOPTS += -p no:cov

# https://github.com/python/mypy/issues/16265
PYTEST_FASTFAIL=

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/mypy-extensions
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/types-psutil
PYTHON_REQUIRED_PACKAGES += library/python/types-setuptools
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/attrs
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/filelock
TEST_REQUIRED_PACKAGES.python += library/python/lxml
TEST_REQUIRED_PACKAGES.python += library/python/mypy-extensions
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/tomli
TEST_REQUIRED_PACKAGES.python += library/python/types-psutil
TEST_REQUIRED_PACKAGES.python += library/python/types-setuptools
TEST_REQUIRED_PACKAGES.python += library/python/typing-extensions
