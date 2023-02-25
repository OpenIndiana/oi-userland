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
#   $WS_TOOLS/python-integrate-project isort
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		isort
HUMAN_VERSION =			5.11.5
COMPONENT_SUMMARY =		isort - A Python utility / library to sort Python imports.
COMPONENT_PROJECT_URL =		https://pycqa.github.io/isort/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/67/63/18cc5c2f9084d3f91ce704f2b5c8e17bedd777244e7732c21a31992b0a78/isort-5.11.5.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:6be1f76a507cb2ecf16c7cf14a37e41609ca082330be4e3436a18ef74add55db
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# isort >= 5.12.0 requires Python >= 3.8
PYTHON_VERSIONS = 3.7

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += runtime/python
