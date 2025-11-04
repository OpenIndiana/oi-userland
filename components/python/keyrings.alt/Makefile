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
#   $WS_TOOLS/python-integrate-project keyrings.alt
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		keyrings.alt
HUMAN_VERSION =			5.0.2
COMPONENT_SUMMARY =		Alternate keyring implementations
COMPONENT_ARCHIVE_HASH =	\
	sha256:8f097ebe9dc8b185106502b8cdb066c926d2180e13b4689fd4771a3eab7d69fb
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_SRC =			keyrings_alt-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-classes
PYTHON_REQUIRED_PACKAGES += library/python/jaraco-context
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/keyring
TEST_REQUIRED_PACKAGES.python += library/python/pycryptodome
TEST_REQUIRED_PACKAGES.python += library/python/pycryptodomex
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-checkdocs
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-enabler
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mypy
