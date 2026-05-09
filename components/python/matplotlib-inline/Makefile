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
#   $WS_TOOLS/python-integrate-project -d python/matplotlib-inline matplotlib_inline
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		matplotlib_inline
HUMAN_VERSION =			0.2.2
COMPONENT_SUMMARY =		Inline Matplotlib backend for Jupyter
COMPONENT_PROJECT_URL =		https://github.com/ipython/matplotlib-inline
COMPONENT_ARCHIVE_HASH =	\
	sha256:72f3fe8fce36b70d4a5b612f899090cd0401deddc4ea90e1572b9f4bfb058c79
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# Testing requires matplotlib.  We do not have it packaged yet.
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += library/python/traitlets
REQUIRED_PACKAGES.python += runtime/python
