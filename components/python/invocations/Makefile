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
#   $WS_TOOLS/python-integrate-project invocations
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		invocations
HUMAN_VERSION =			3.3.0
COMPONENT_SUMMARY =		invocations - Common/best-practice Invoke tasks and collections
COMPONENT_PROJECT_URL =		https://invocations.readthedocs.io
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/93/6d/094a0bdc46e2e00ad00e02415525c708c708b0509085727853a62cea6f4c/invocations-3.3.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:caa950dad1842f89074e4bc241958dc3acc3b36c39a94e8c08c3ea5b5f7e992f
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = setup.py

include $(WS_MAKE_RULES)/common.mk

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += dev-requirements.txt

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/blessings
PYTHON_REQUIRED_PACKAGES += library/python/invoke
PYTHON_REQUIRED_PACKAGES += library/python/releases
PYTHON_REQUIRED_PACKAGES += library/python/semantic-version
PYTHON_REQUIRED_PACKAGES += library/python/tabulate
PYTHON_REQUIRED_PACKAGES += library/python/tqdm
PYTHON_REQUIRED_PACKAGES += library/python/twine
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/black
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/flake8
TEST_REQUIRED_PACKAGES.python += library/python/icecream
TEST_REQUIRED_PACKAGES.python += library/python/invoke
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-relaxed
TEST_REQUIRED_PACKAGES.python += library/python/releases
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
TEST_REQUIRED_PACKAGES.python += library/python/watchdog
