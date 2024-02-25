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
#   $WS_TOOLS/python-integrate-project setuptools-rust
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		setuptools-rust
HUMAN_VERSION =			1.9.0
COMPONENT_SUMMARY =		setuptools-rust - Setuptools Rust extension plugin
COMPONENT_PROJECT_URL =		https://github.com/PyO3/setuptools-rust
COMPONENT_ARCHIVE_HASH =	\
	sha256:704df0948f2e4cc60c2596ad6e840ea679f4f43e58ed4ad0c1857807240eab96
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Tests are supposed to run using 'nox -s test' (see .github/workflows/ci.yml
# in the git repo).  That in turn calls pytest with 'setuptools_rust', and
# 'tests' parameters (see noxfile.py).  The 'pytest' test style is currently
# automatically detected so we just add needed parameters as test targets.
COMPONENT_TEST_TARGETS += setuptools_rust
COMPONENT_TEST_TARGETS += tests

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/semantic-version
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
