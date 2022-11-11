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
#   $WS_TOOLS/python-integrate-project py
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		py
COMPONENT_VERSION =		1.11.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		py - library with cross-python path, ini-parsing, io, code, log facilities
COMPONENT_PROJECT_URL =		https://py.readthedocs.io/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/98/ff/fec109ceb715d2a6b4c4a85a61af3b40c723a961e8828319fbcb15b868dc/py-1.11.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:51c75c4126074b472f746a24399ad32f6053d1b34b68d2fa41e558e6f4a98719
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - tox (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += runtime/python
