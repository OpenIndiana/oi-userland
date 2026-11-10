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
#   $WS_TOOLS/python-integrate-project -d python/python-sbom python_sbom
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		python_sbom
HUMAN_VERSION =			0.5.0
COMPONENT_SUMMARY =		SBOMs for Python distributions: write PEP 770 CycloneDX SBOMs into wheels.
COMPONENT_PROJECT_URL =		https://github.com/tox-dev/python-sbom
COMPONENT_ARCHIVE_HASH =	\
	sha256:fc7b2c46fa40f52e587ac59cada775e83dcac231fafa90b7a71c3554527ddfb6
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# python-sbom needs Python >= 3.11
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# We have no license-expression packaged yet.
COMPONENT_POST_UNPACK_ACTION += $(RM) $(COMPONENT_SRC)/src/python_sbom/_validate/_licenses.py ;
# We have no jsonschema-rs, license-expression, and spdx-tools packaged yet.
COMPONENT_POST_UNPACK_ACTION += $(RM) $(COMPONENT_SRC)/src/python_sbom/_validate/_schemas.py ;

# We have no jsonschema-rs packaged yet.
PYTEST_ADDOPTS += --deselect tests/_validate/test_document.py::test_schema_violation
PYTEST_ADDOPTS += --ignore tests/_model/test_iri.py
# We have no spdx-tools packaged yet.
PYTEST_ADDOPTS += --deselect tests/_validate/test_document.py::test_spdx_rendering_must_validate
PYTEST_ADDOPTS += --deselect tests/_validate/test_document.py::test_spdx_rendering_must_parse
PYTEST_ADDOPTS += --deselect tests/_validate/test_document.py::test_unexpected_error_is_reported
PYTEST_ADDOPTS += --ignore tests/_formats/test_spdx.py
PYTEST_ADDOPTS += --ignore tests/_validate/test_schemas.py
# We have no license-expression packaged yet.
PYTEST_ADDOPTS += --ignore tests/_validate/test_licenses.py

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatch-fancy-pypi-readme
REQUIRED_PACKAGES.python += library/python/hatch-vcs
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += library/python/installer
REQUIRED_PACKAGES.python += library/python/packageurl-python
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/zipremove
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/flit-core
TEST_REQUIRED_PACKAGES.python += library/python/hatchling
TEST_REQUIRED_PACKAGES.python += library/python/installer
TEST_REQUIRED_PACKAGES.python += library/python/pdm-backend
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
