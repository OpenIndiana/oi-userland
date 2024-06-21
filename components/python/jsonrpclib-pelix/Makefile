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
#   $WS_TOOLS/python-integrate-project jsonrpclib-pelix
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jsonrpclib-pelix
HUMAN_VERSION =			0.4.3.3
COMPONENT_SUMMARY =		This project is an implementation of the JSON-RPC v2.0 specification (backwards-compatible) as a client library, for Python 2.7 and Python 3. This version is a fork of jsonrpclib by Josh Marshall, made to be also usable with Pelix/iPOPO remote services.
COMPONENT_PROJECT_URL =		http://github.com/tcalmant/jsonrpclib/
COMPONENT_ARCHIVE_HASH =	\
	sha256:c494fe7100b1139b1311469c28bc32d1cb92e4ff1f4511fb71d6807205dc3773
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://github.com/tcalmant/jsonrpclib/issues/61
COMPONENT_PREP_ACTION += $(CHMOD) +x $(SOURCE_DIR)/tests/cgi-bin/cgi_server.py ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
