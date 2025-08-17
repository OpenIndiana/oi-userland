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
#   $WS_TOOLS/python-integrate-project -d python/setuptools-scm setuptools_scm
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		setuptools_scm
HUMAN_VERSION =			9.2.0
COMPONENT_SUMMARY =		the blessed package to manage your versions by scm tags
COMPONENT_ARCHIVE_HASH =	\
	sha256:6662c9b9497b6c9bf13bead9d7a9084756f68238302c5ed089fb4dbd29d102d7
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - flit_scm (test bootstrap)
# - hatch_vcs (test bootstrap)
# - importlib_metadata
# - pluggy (test bootstrap)
# - pytest (test bootstrap)
# - zipp
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Random directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|/tmp/.*/garbage[^/]*|\$$(TMPDIR)|'"

# https://github.com/pypa/setuptools-scm/issues/1204
PYTEST_ADDOPTS += --deselect testing/test_functions.py::test_dump_version_mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/build
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/mypy
TEST_REQUIRED_PACKAGES.python += library/python/pip
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist
TEST_REQUIRED_PACKAGES.python += library/python/rich
TEST_REQUIRED_PACKAGES.python += library/python/typing-extensions
TEST_REQUIRED_PACKAGES.python += library/python/wheel
