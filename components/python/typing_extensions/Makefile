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
#   $WS_TOOLS/python-integrate-project typing_extensions
#

BUILD_STYLE = pyproject
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		typing_extensions
HUMAN_VERSION =			4.16.0
COMPONENT_SUMMARY =		Backported and Experimental Type Hints for Python 3.9+
COMPONENT_ARCHIVE_HASH =	\
	sha256:dc983d19a509c94dba722ee6abd33940f7c05a89e243c47e907eb4db6f1a43e5
COMPONENT_LICENSE =		PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - setuptools-scm
# - virtualenv (test bootstrap)
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
