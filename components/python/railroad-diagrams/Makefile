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
#   $WS_TOOLS/python-integrate-project railroad-diagrams
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		railroad-diagrams
HUMAN_VERSION =			3.0.1
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Generate SVG railroad syntax diagrams, like on JSON.org.
COMPONENT_PROJECT_URL =		https://github.com/tabatkins/railroad-diagrams
COMPONENT_ARCHIVE_HASH =	\
	sha256:a91332bac900cb3c367331fa9b699f0897bcf86b7264f65458675df430d04ce3
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = none

# The sdist is missing tests:
# https://github.com/tabatkins/railroad-diagrams/issues/100
# And there are no git tags to get tests from github tarball:
# https://github.com/tabatkins/railroad-diagrams/issues/91

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
