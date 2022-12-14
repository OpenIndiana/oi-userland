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
#   $WS_TOOLS/python-integrate-project characteristic
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		characteristic
COMPONENT_VERSION =		14.3.0
COMPONENT_SUMMARY =		characteristic - Python attributes without boilerplate.
COMPONENT_PROJECT_URL =		https://characteristic.readthedocs.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/dc/66/54b7a4758ea44fbc93895c7745060005272560fb2c356f2a6f7448ef9a80/characteristic-14.3.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:ded68d4e424115ed44e5c83c2a901a0b6157a959079d7591d92106ffd3ada380
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# We need to override the default tox test style because it is just
# encapsulated setup.py test style.  It is failing miserably.
TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
