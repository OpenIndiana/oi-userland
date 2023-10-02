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
#   $WS_TOOLS/python-integrate-project pydantic
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pydantic
HUMAN_VERSION =			1.10.13
COMPONENT_SUMMARY =		pydantic - Data validation using Python type hints
COMPONENT_PROJECT_URL =		https://github.com/pydantic/pydantic
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/51/cd/721eb771f3f09f60de0807e240c3acf44c38828d0ced869fe8df7e79801b/pydantic-1.10.13.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:32c8b48dcd3b2ac4e78b0ba4af3a2c2eb6048cb75202f0ea7b34feb740efc340
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://github.com/PyO3/setuptools-rust/issues/358
TEST_CONFLICTING_PACKAGES.python += library/python/setuptools-rust

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
