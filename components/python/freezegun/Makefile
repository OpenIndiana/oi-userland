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
#   $WS_TOOLS/python-integrate-project freezegun
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		freezegun
HUMAN_VERSION =			1.3.1
COMPONENT_SUMMARY =		freezegun - Let your Python tests travel through time
COMPONENT_PROJECT_URL =		https://github.com/spulec/freezegun
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/76/49/1b9dd9480d29dc8d226772fe4dce6991ac013739d0c1949bcd46fb6cd7d4/freezegun-1.3.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:48984397b3b58ef5dfc645d6a304b0060f612bcecfdaaf45ce8aff0077a6cb6a
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/python-dateutil
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coveralls
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/python-dateutil
