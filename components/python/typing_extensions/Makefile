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
#   $WS_TOOLS/python-integrate-project typing_extensions
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		typing_extensions
HUMAN_VERSION =			4.4.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		typing_extensions - Backported and Experimental Type Hints for Python 3.7+
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/e3/a7/8f4e456ef0adac43f452efc2d0e4b242ab831297f1bac60ac815d37eb9cf/typing_extensions-4.4.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1511434bb92bf8dd198c12b1cc812e800d4181cfcb867674e0f8279cc93087aa
COMPONENT_LICENSE =		PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - importlib_metadata
# - setuptools_scm
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
