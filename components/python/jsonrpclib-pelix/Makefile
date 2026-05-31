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
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jsonrpclib_pelix
HUMAN_VERSION =			1.1.0
COMPONENT_SUMMARY =		JSON-RPC v2.0 client and server for Python 2.7 and Python 3.6+ usable with Pelix/iPOPO remote services.
COMPONENT_PROJECT_URL =		https://github.com/tcalmant/jsonrpclib/
COMPONENT_ARCHIVE_HASH =	\
	sha256:379a3c9b3dd478727419587aa7cf14bb6ff0e64301decc0ffa98f710f6bfec1e
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# pid is random
# see also https://github.com/tcalmant/jsonrpclib/issues/74
COMPONENT_TEST_TRANSFORMS += "-e 's/(pid=[0-9]\{1,\})/(pid=\$$(PID))/'"

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/hatchling
REQUIRED_PACKAGES.python += runtime/python
