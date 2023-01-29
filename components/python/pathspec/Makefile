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
#   $WS_TOOLS/python-integrate-project pathspec
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pathspec
HUMAN_VERSION =			0.11.0
COMPONENT_SUMMARY =		pathspec - Utility library for gitignore style pattern matching of file paths.
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/f4/8e/f91cffb32740b251cff04cad1e7cdd2c710582c735a01f56307316c148f2/pathspec-0.11.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:64d338d4e0914e91c1792321e6907b5a593f1ab1851de7fc269557a21b30ebbc
COMPONENT_LICENSE =		MPL-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - hatchling (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
