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
#   $WS_TOOLS/python-integrate-project lazy
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		lazy
HUMAN_VERSION =			2.0
COMPONENT_SUMMARY =		Lazy attributes for Python objects
COMPONENT_PROJECT_URL =		https://github.com/stefanholek/lazy
COMPONENT_ARCHIVE_HASH =	\
	sha256:f92ec0d32dd6bd115ddec4e3323473ebc0b682ad58c6aca78ebfd9e6d1aa5777
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Force verbose output via tox posargs
TOX_POSARGS += -v

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
