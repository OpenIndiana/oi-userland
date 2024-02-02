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
#   $WS_TOOLS/python-integrate-project cachecontrol
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cachecontrol
HUMAN_VERSION =			0.14.0
COMPONENT_SUMMARY =		cachecontrol - httplib2 caching for requests
COMPONENT_PROJECT_URL =		https://pypi.org/project/CacheControl/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/06/55/edea9d90ee57ca54d34707607d15c20f72576b96cb9f3e7fc266cb06b426/cachecontrol-0.14.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:7db1195b41c81f8274a7bbd97c956f44e8348265a1bc7641c37dfebc39f0c938
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Remove timestamp and random port number
COMPONENT_TEST_TRANSFORMS += "-e 's/ \{1,\}\[.*ENGINE HTTP Server.*//'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += library/python/msgpack
PYTHON_REQUIRED_PACKAGES += library/python/requests
PYTHON_REQUIRED_PACKAGES += runtime/python
