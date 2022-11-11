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
#   $WS_TOOLS/python-integrate-project exceptiongroup
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		exceptiongroup
COMPONENT_VERSION =		1.0.1
COMPONENT_SUMMARY =		exceptiongroup - Backport of PEP 654 (exception groups)
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/13/55/43ff6658a50a7f722d2f904810b42514c23a5d649d8a5d890cdc16b617de/exceptiongroup-1.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:73866f7f842ede6cb1daa42c4af078e2035e5f7607f0e2c762cc51bb31bbe7b2
COMPONENT_LICENSE =		MIT AND PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - pytest (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-scm
PYTHON_REQUIRED_PACKAGES += runtime/python
