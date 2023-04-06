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
#   $WS_TOOLS/python-integrate-project inflect
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		inflect
HUMAN_VERSION =			6.0.4
COMPONENT_SUMMARY =		inflect - Correctly generate plurals, singular nouns, ordinals, indefinite articles; convert numbers to words
COMPONENT_PROJECT_URL =		https://github.com/jaraco/inflect
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/3b/9b/6e44523788cadec2a2bef2632c21264a74ab172cf9a13fab5c94b10db7f2/inflect-6.0.4.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1842649a17b6cad66812a5c9bdfacb6310e1e7b6dd8a31f026766df1b62612eb
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/tholo/pytest-flake8/issues/92
PYTEST_ADDOPTS += -p no:flake8

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pydantic
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/pygments
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-black
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-flake8
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
