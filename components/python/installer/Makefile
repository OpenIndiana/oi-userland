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
#   $WS_TOOLS/python-integrate-project installer
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		installer
HUMAN_VERSION =			0.6.0
COMPONENT_SUMMARY =		installer - A library for installing Python wheels.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/c9/ab/a9141dc175ec7b620fffe7e0295251a7b6a0ffb4325d64aeb128dff8c698/installer-0.6.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f3bd36cd261b440a88a1190b1becca0578fee90b4b62decc796932fdd5ae8839
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - Userland build framework (see pyproject.mk)
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
