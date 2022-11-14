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
#   $WS_TOOLS/python-integrate-project testpath
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		testpath
COMPONENT_VERSION =		0.6.0
COMPONENT_SUMMARY =		testpath - Test utilities for code working with files and commands
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/08/ad/a3e7d580902f57e31d2181563fc4088894692bb6ef79b816344f27719cdc/testpath-0.6.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:2f1b97e6442c02681ebe01bd84f531028a7caea1af3825000f52345c30285e0f
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# cli-32.exe and cli-64.exe are needed for Windows only, so drop them
GENERATE_EXTRA_CMD += | $(GNU_GREP) -v -E '/cli-(32|64)\.exe$$'

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
