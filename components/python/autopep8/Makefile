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

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		autopep8
HUMAN_VERSION =			2.0.2
COMPONENT_SUMMARY =		autopep8 - A tool that automatically formats Python code to conform to the PEP 8 style guide
COMPONENT_PROJECT_URL =		https://github.com/hhatto/autopep8
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b2/03/49cb49b37a4d51721ece9c628eb9441f9a4e26ee98ad6e5505238d5b2d7a/autopep8-2.0.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f9849cdd62108cb739dbcdbfb7fdcc9a30d1b63c4cc3e1c1f893b5360941b61c
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Normalize random temporary directory name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/autopep8test\)......../|\1XXXXXXXX/|'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/pycodestyle
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/tomli
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pycodestyle
TEST_REQUIRED_PACKAGES.python += library/python/pydiff
