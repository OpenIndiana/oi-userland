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
#   $WS_TOOLS/python-integrate-project pytest-console-scripts
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-console-scripts
HUMAN_VERSION =			1.4.1
COMPONENT_SUMMARY =		pytest-console-scripts - Pytest plugin for testing console scripts
COMPONENT_PROJECT_URL =		https://github.com/kvas-it/pytest-console-scripts
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/a1/85/2fbafaea1fa948497ef7f52574448e7ff99236c71a1519e312b8a2f01008/pytest-console-scripts-1.4.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5a826ed84cc0afa202eb9e44381d7d762f7bdda8e0c23f9f79a7f1f44cf4a895
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# pytest-console-scripts >= 1.4.1 requires Python >= 3.8
PYTHON_VERSIONS := $(filter-out 3.7, $(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
