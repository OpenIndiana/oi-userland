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
#   $WS_TOOLS/python-integrate-project humanize
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		humanize
HUMAN_VERSION =			4.7.0
COMPONENT_SUMMARY =		humanize - Python humanize utilities
COMPONENT_PROJECT_URL =		https://github.com/python-humanize/humanize
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/69/86/34d04afc5c33a31f4e9939f857e28fc9d039440f29b99a34f2190f0ab0ac/humanize-4.7.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:7ca0e43e870981fa684acb5b062deb307218193bca1a01f2b2676479df849b3a
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENCE

include $(WS_MAKE_RULES)/common.mk

# https://github.com/python-humanize/humanize/issues/105
PYTEST_ADDOPTS += -p no:randomly

# https://github.com/jaraco/pytest-enabler/issues/8
TEST_CONFLICTING_PACKAGES.python += library/python/pytest-enabler

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/freezegun
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
