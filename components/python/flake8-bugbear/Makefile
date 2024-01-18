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
HUMAN_VERSION =			24.1.17
COMPONENT_SUMMARY =		flake8-bugbear - A plugin for flake8 finding likely bugs and design problems in your program. Contains warnings that don't belong in pyflakes and pycodestyle.
COMPONENT_PROJECT_URL =		https://github.com/PyCQA/flake8-bugbear
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f1/30/4cbcbbef8820b504a904cdd6927fe031aabca61b63667993b39368a7577c/flake8-bugbear-24.1.17.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:bcb388a4f3b516258749b1e690ee394c082eff742f44595e3754cf5c7781c2c7
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Force verbose output via tox posargs
COMPONENT_TEST_TARGETS += -- -v

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/attrs
PYTHON_REQUIRED_PACKAGES += library/python/flake8
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
