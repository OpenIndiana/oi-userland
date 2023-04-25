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
#   $WS_TOOLS/python-integrate-project elasticsearch
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		elasticsearch
HUMAN_VERSION =			8.7.0
COMPONENT_SUMMARY =		elasticsearch - Python client for Elasticsearch
COMPONENT_PROJECT_URL =		https://github.com/elastic/elasticsearch-py
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/fe/af/c3822861b6d965c2a588ce4159d870f6d906e4cc74a4f9d1ced737bd70be/elasticsearch-8.7.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1849356db4192fbb75b2b8f3d55edb0fb07f8d855f386b318a7889222b49591f
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# https://github.com/elastic/elasticsearch-py/issues/2205
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/elastic-transport
PYTHON_REQUIRED_PACKAGES += runtime/python
