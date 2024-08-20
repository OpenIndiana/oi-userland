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
#   $WS_TOOLS/python-integrate-project jedi
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jedi
HUMAN_VERSION =			0.19.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		An autocompletion tool for Python that can be used for text editors.
COMPONENT_PROJECT_URL =		https://github.com/davidhalter/jedi
COMPONENT_ARCHIVE_HASH =	\
	sha256:cf0496f3651bc65d7174ac1b7d043eff454892c708a87d1b683e57b569927ffd
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS_EXTRAS += testing

# Following tests fails with the 'pkg' project installed.
PYTEST_ADDOPTS += --deselect test/test_api/test_classes.py::test_inheritance_module_path
PYTEST_ADDOPTS += --deselect test/test_inference/test_imports.py::test_correct_zip_package_behavior
PYTEST_ADDOPTS += --deselect test/test_inference/test_imports.py::test_find_module_package_zipped
PYTEST_ADDOPTS += --deselect test/test_inference/test_imports.py::test_zip_package_import_complete

# https://github.com/davidhalter/jedi/issues/2022
PYTEST_ADDOPTS += --deselect test/test_api/test_completion.py::test_complete_expanduser

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/parso
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/attrs
TEST_REQUIRED_PACKAGES.python += library/python/colorama
TEST_REQUIRED_PACKAGES.python += library/python/docopt
TEST_REQUIRED_PACKAGES.python += library/python/pytest
