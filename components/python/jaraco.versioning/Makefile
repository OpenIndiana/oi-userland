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
#   $WS_TOOLS/python-integrate-project -d python/jaraco.versioning jaraco_versioning
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jaraco_versioning
HUMAN_VERSION =			1.1.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		More sophisticated version manipulation (than packaging)
COMPONENT_PROJECT_URL =		https://github.com/jaraco/jaraco.versioning
COMPONENT_ARCHIVE_HASH =	\
	sha256:5ab6e6751157d31a6405036b3f8ee5a28f4d1df7244cd099aa788f4b57421d0f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_SRC =			jaraco.versioning-$(HUMAN_VERSION)

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/packaging
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/setuptools-scm
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
