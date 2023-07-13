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
#   $WS_TOOLS/python-integrate-project diff_cover
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		diff_cover
HUMAN_VERSION =			7.6.1
COMPONENT_SUMMARY =		diff_cover - Run coverage and linting reports on diffs
COMPONENT_PROJECT_URL =		https://github.com/Bachmann1234/diff-cover
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/2d/6c/41c8d3f0780b5de55cea25453a5f2a1160f4ba2d8760c01bbf6cf2669d66/diff_cover-7.6.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:78dd8368789fff3bf5f5f3f696826da9cf1f54f364e4a3748026722fc5ec514f
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:checkdocs
PYTEST_ADDOPTS += -p no:cov
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/chardet
PYTHON_REQUIRED_PACKAGES += library/python/jinja2
PYTHON_REQUIRED_PACKAGES += library/python/pluggy
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += library/python/pygments
PYTHON_REQUIRED_PACKAGES += runtime/python
