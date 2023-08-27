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
#   $WS_TOOLS/python-integrate-project pluggy
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pluggy
HUMAN_VERSION =			1.3.0
COMPONENT_SUMMARY =		pluggy - plugin and hook calling mechanisms for python
COMPONENT_PROJECT_URL =		https://github.com/pytest-dev/pluggy
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/36/51/04defc761583568cae5fd533abda3d40164cbdcf22dee5b7126ffef68a40/pluggy-1.3.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:cf61ae8f126ac6f7c451172cf30e3e43d3ca77615509771b3a984a0730651e12
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - hatchling (test bootstrap)
# - pytest (test bootstrap)
# - tox (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Make sure pytest is called indirectly
COMPONENT_TEST_ENV += _PLUGGY_TOX_CMD="python -m pytest"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark
