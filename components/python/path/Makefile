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
#   $WS_TOOLS/python-integrate-project path
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		path
HUMAN_VERSION =			16.9.0
COMPONENT_SUMMARY =		path - A module wrapper for os.path
COMPONENT_PROJECT_URL =		https://github.com/jaraco/path
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/8d/50/2a1a3287715c87d135dd1dcbd9f7bca4200302cfcc8c28ced1a8035d7894/path-16.9.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:dfd31c2af60e8889a13538bef302ade7adacdb5351836be22638e2349ddd5d7b
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Revert back unneeded PYV normalizations
COMPONENT_TEST_TRANSFORMS += "-e 's/py\$$(PYV)compat/py$(shell echo $(PYTHON_VERSION) | tr -d .)compat/'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/appdirs
TEST_REQUIRED_PACKAGES.python += library/python/more-itertools
TEST_REQUIRED_PACKAGES.python += library/python/packaging
TEST_REQUIRED_PACKAGES.python += library/python/pygments
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-black
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
