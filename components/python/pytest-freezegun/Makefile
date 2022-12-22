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
#   $WS_TOOLS/python-integrate-project pytest-freezegun
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-freezegun
HUMAN_VERSION =			0.4.2
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		pytest-freezegun - Wrap tests with fixtures in freeze_time
COMPONENT_PROJECT_URL =		https://github.com/ktosiek/pytest-freezegun
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f0/e3/c39d7c3d3afef5652f19323f3483267d7e6b0d9911c3867e10d6e2d3c9ae/pytest-freezegun-0.4.2.zip
COMPONENT_ARCHIVE_HASH =	\
	sha256:19c82d5633751bf3ec92caa481fb5cffaac1787bd485f0df6436fd6242176949
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

COMPONENT_ARCHIVE =		$(COMPONENT_SRC).zip

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/freezegun
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += runtime/python
