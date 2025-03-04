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
#   $WS_TOOLS/python-integrate-project -d python/jsonrpclib-pelix jsonrpclib_pelix
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jsonrpclib_pelix
HUMAN_VERSION =			0.4.3.4
COMPONENT_SUMMARY =		JSON-RPC v2.0 client and server for Python 2.7 and Python 3.6+ usable with Pelix/iPOPO remote services.
COMPONENT_PROJECT_URL =		http://github.com/tcalmant/jsonrpclib/
COMPONENT_ARCHIVE_HASH =	\
	sha256:e82d6f4da907a7d111ef93fd2361c8c20b79d248be4fe99678e08626aa8fcbef
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://github.com/tcalmant/jsonrpclib/issues/61
COMPONENT_PREP_ACTION += $(CHMOD) +x $(SOURCE_DIR)/tests/cgi-bin/cgi_server.py ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += runtime/python
