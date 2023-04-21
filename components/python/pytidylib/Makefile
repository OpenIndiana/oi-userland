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
#   $WS_TOOLS/python-integrate-project pytidylib
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytidylib
HUMAN_VERSION =			0.3.2
COMPONENT_SUMMARY =		pytidylib - Python wrapper for HTML Tidy (tidylib) on Python 2 and 3
COMPONENT_PROJECT_URL =		http://countergram.com/open-source/pytidylib/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/2d/5e/4d2b5e2d443d56f444e2a3618eb6d044c97d14bf47cab0028872c0a468e0/pytidylib-0.3.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:22b1c8d75970d8064ff999c2369e98af1d0685417eda4c829a5c9f56764b0af3
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Testing fails with the checkdocs plugin installed
PYTEST_ADDOPTS += -p no:checkdocs

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
