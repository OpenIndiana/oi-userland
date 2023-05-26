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
HUMAN_VERSION =			8.8.0
COMPONENT_SUMMARY =		elasticsearch - Python client for Elasticsearch
COMPONENT_PROJECT_URL =		https://github.com/elastic/elasticsearch-py
COMPONENT_ARCHIVE_URL =		\
	https://github.com/elastic/elasticsearch-py/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:9a8df5885d6a1aede72bc877bb53125ec27992c420e242293a24e8fcecae5160
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

COMPONENT_SRC = elasticsearch-py-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/elastic-transport
PYTHON_REQUIRED_PACKAGES += runtime/python
