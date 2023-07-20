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
#   $WS_TOOLS/python-integrate-project dnspython
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dnspython
HUMAN_VERSION =			2.4.0
COMPONENT_SUMMARY =		dnspython - DNS toolkit
COMPONENT_PROJECT_URL =		https://www.dnspython.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/bd/5f/45f60fd7b03a1bef883a0eb4f9b6465628c1977393be45802eef1962571d/dnspython-2.4.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:758e691dbb454d5ccf4e1b154a19e52847f79e21a42fef17b969144af29a4e6c
COMPONENT_LICENSE =		ISC
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Disable some plugins to get tests passed
PYTEST_ADDOPTS += -p no:mypy

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/httpcore
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += library/python/sniffio
PYTHON_REQUIRED_PACKAGES += runtime/python
