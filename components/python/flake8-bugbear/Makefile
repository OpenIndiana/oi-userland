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
#   $WS_TOOLS/python-integrate-project flake8-bugbear
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		flake8-bugbear
HUMAN_VERSION =			23.6.5
COMPONENT_SUMMARY =		flake8-bugbear - A plugin for flake8 finding likely bugs and design problems in your program. Contains warnings that don't belong in pyflakes and pycodestyle.
COMPONENT_PROJECT_URL =		https://github.com/PyCQA/flake8-bugbear
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/00/c5/e95dcb8f8a882858481e324d33853cc83701d581b51034079881b391c715/flake8-bugbear-23.6.5.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:8631e1071c9d85d24a615f235565c16c9a2ac57add4a14636d331bf9f4ef14fa
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# flake8-bugbear >= 23.3.23 requires Python >= 3.8.1
PYTHON_VERSIONS := $(filter-out 3.7, $(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/flake8
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/hypothesmith
