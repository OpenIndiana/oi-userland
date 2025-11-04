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
#   $WS_TOOLS/python-integrate-project autopep8
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		autopep8
HUMAN_VERSION =			2.3.2
COMPONENT_SUMMARY =		A tool that automatically formats Python code to conform to the PEP 8 style guide
COMPONENT_ARCHIVE_HASH =	\
	sha256:89440a4f969197b69a995e4ce0661b031f455a9f776d2c5ba3dbd83466931758
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Normalize random temporary directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/autopep8test\)......../|\1XXXXXXXX/|'"
# Normalize random temporary file name
COMPONENT_TEST_TRANSFORMS += "-e 's|^/tmp/.\{11\}\.py|/tmp/XXXXXXXXXXX.py|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pycodestyle
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pycodestyle
TEST_REQUIRED_PACKAGES.python += library/python/pydiff
