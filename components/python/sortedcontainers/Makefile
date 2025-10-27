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
#   $WS_TOOLS/python-integrate-project sortedcontainers
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		sortedcontainers
HUMAN_VERSION =			2.4.0
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Sorted Containers -- Sorted List, Sorted Dict, Sorted Set
COMPONENT_PROJECT_URL =		http://www.grantjenks.com/docs/sortedcontainers/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/grantjenks/python-sortedcontainers/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:70e22f4fd29b204f75f989e3c1e847aa1de267a028aab4233c0db783aaff78c1
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_SRC =			python-sortedcontainers-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
