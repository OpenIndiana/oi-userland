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
HUMAN_VERSION =			0.19.0
COMPONENT_SUMMARY =		jedi - An autocompletion tool for Python that can be used for text editors.
COMPONENT_PROJECT_URL =		https://github.com/davidhalter/jedi
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/57/38/4ac6f712c308de92af967142bd67e9d27e784ea5a3524c9e84f33507d82f/jedi-0.19.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:bcf9894f1753969cbac8022a8c2eaee06bfa3724e4192470aaffe7eb6272b0c4
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:black
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/parso
PYTHON_REQUIRED_PACKAGES += runtime/python
