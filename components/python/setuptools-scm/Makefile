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
#   $WS_TOOLS/python-integrate-project setuptools-scm
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		setuptools-scm
HUMAN_VERSION =			8.0.2
COMPONENT_SUMMARY =		setuptools-scm - the blessed package to manage your versions by scm tags
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/51/11/58d3bdef61f2090330292b52d390d57b76dfc08f003174952eff0fafa10e/setuptools-scm-8.0.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:e45c8c87719b753b6d47cf09907d1239540c7e150cd44f06f658b602f402b005
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

# https://github.com/PyO3/setuptools-rust/issues/358
TEST_CONFLICTING_PACKAGES.python += library/python/setuptools-rust

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/rich
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/rich
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/virtualenv
