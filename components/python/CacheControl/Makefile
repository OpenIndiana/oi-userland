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
#   $WS_TOOLS/python-integrate-project CacheControl
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		CacheControl
HUMAN_VERSION =			0.13.0
COMPONENT_SUMMARY =		CacheControl - httplib2 caching for requests
COMPONENT_PROJECT_URL =		https://github.com/ionrock/cachecontrol
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/9d/47/9bdf134012537324bbdebe84c144cc8fab08f148fc6c9ce89b8eefff1cb0/CacheControl-0.13.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:fd3fd2cb0ca66b9a6c1d56cc9709e7e49c63dbd19b1b1bcbd8d3f94cedfe8ce5
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Remove timestamp and random port number
COMPONENT_TEST_TRANSFORMS += "-e 's/ \[.*ENGINE HTTP Server.*//'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/msgpack
PYTHON_REQUIRED_PACKAGES += library/python/requests
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
