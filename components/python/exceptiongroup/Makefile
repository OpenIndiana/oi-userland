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
HUMAN_VERSION =			1.1.3
COMPONENT_SUMMARY =		exceptiongroup - Backport of PEP 654 (exception groups)
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/c2/e1/5561ad26f99b7779c28356f73f69a8b468ef491d0f6adf20d7ed0ac98ec1/exceptiongroup-1.1.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:097acd85d473d75af5bb98e41b61ff7fe35efe6675e4f9370ec6ec5126d160e9
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
TEST_REQUIRED_PACKAGES.python += library/python/pytest
