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
#   $WS_TOOLS/python-integrate-project dunamai
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dunamai
HUMAN_VERSION =			1.19.2
COMPONENT_SUMMARY =		dunamai - Dynamic version generation
COMPONENT_PROJECT_URL =		https://github.com/mtkennerly/dunamai
COMPONENT_ARCHIVE_HASH =	\
	sha256:3be4049890763e19b8df1d52960dbea60b3e263eb0c96144a677ae0633734d2e
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Testing dependencies for this project are maintained using poetry.  We
# neither do have poetry packaged yet, nor support listing poetry dependencies
# without poetry.  For now we just hope all required testing dependencies are
# installed.

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/poetry-core
PYTHON_REQUIRED_PACKAGES += runtime/python
