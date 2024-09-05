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
#   $WS_TOOLS/python-integrate-project -d python/pytest-enabler pytest_enabler
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest_enabler
HUMAN_VERSION =			3.2.0
COMPONENT_SUMMARY =		Enable installed pytest plugins
COMPONENT_ARCHIVE_HASH =	\
	sha256:bbb26fb4b53c1e7d651273b48dc378593d6e5a351e7ff1752ec410d51a40faa1
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-resources
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-context
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-functools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/toml
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
TEST_REQUIRED_PACKAGES.python += library/python/types-toml
