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
#   $WS_TOOLS/python-integrate-project PySocks
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		PySocks
COMPONENT_VERSION =		1.7.1
COMPONENT_SUMMARY =		PySocks - A Python SOCKS client module. See https://github.com/Anorov/PySocks for more information.
COMPONENT_PROJECT_URL =		https://github.com/Anorov/PySocks
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/bd/11/293dd436aea955d45fc4e8a35b6ae7270f5b8e00b53cf6c024c83b657a11/PySocks-1.7.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:3f8804571ebe159c380ac6de37643bb4685970655d3bba243530d6558b799aa0
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# To test we need 3proxy (https://3proxy.org/), but it is not packaged for
# OpenIndiana (yet).  See also https://github.com/Anorov/PySocks/issues/136
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
