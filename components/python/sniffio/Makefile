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
#   $WS_TOOLS/python-integrate-project sniffio
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sniffio
HUMAN_VERSION =			1.3.1
COMPONENT_SUMMARY =		sniffio - Sniff out which async library your code is running under
COMPONENT_PROJECT_URL =		https://github.com/python-trio/sniffio
COMPONENT_ARCHIVE_HASH =	\
	sha256:f4324edc670a0f49750a81b895f35c3adb843cca46f0530f79fc1babb23789dc
COMPONENT_LICENSE =		Apache-2.0 OR MIT

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += test-requirements.txt

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/curio
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
