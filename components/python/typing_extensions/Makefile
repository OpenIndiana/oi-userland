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
HUMAN_VERSION =			4.6.2
COMPONENT_SUMMARY =		typing_extensions - Backported and Experimental Type Hints for Python 3.7+
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/be/fc/3d12393d634fcb31d5f4231c28feaf4ead225124ba08021046317d5f450d/typing_extensions-4.6.2.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:06006244c70ac8ee83fa8282cb188f697b8db25bc8b4df07be1873c43897060c
COMPONENT_LICENSE =		PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - importlib_metadata
# - platformdirs (test bootstrap)
# - setuptools_scm
# - tox (test bootstrap)
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
