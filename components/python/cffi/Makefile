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
#   $WS_TOOLS/python-integrate-project cffi
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cffi
HUMAN_VERSION =			1.17.1
COMPONENT_SUMMARY =		Foreign Function Interface for Python calling C code.
COMPONENT_PROJECT_URL =		http://cffi.readthedocs.org
COMPONENT_ARCHIVE_HASH =	\
	sha256:1c39c6016c32bc48dd54561950ebd6836e1670f2ae46128f67cf49e789c52824
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Normalize pointers
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{12\}/\$$(POINTER)/g'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pycparser
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += system/library
