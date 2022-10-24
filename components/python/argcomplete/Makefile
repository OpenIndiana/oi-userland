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
#   $WS_TOOLS/python-integrate-project argcomplete
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		argcomplete
COMPONENT_VERSION =		1.12.3
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		argcomplete - Bash tab completion for argparse
COMPONENT_PROJECT_URL =		https://github.com/kislyuk/argcomplete
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/6a/b4/3b1d48b61be122c95f4a770b2f42fc2552857616feba4d51f34611bd1352/argcomplete-1.12.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:2c7dbffd8c045ea534921e63b0be6fe65e88599990d8dc408ac8c542b72a5445
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.rst

include $(WS_MAKE_RULES)/common.mk

# Fish is optional dependency for tests, so require it to make sure we get
# consistent test results.
#
# Unfortunately, Fish tests sometimes fails so test results are not very
# consistent anyway.
REQUIRED_PACKAGES += shell/fish

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += shell/ksh93
