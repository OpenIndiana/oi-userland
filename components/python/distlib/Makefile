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
#   $WS_TOOLS/python-integrate-project distlib
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		distlib
COMPONENT_VERSION =		0.3.6
COMPONENT_SUMMARY =		distlib - Distribution utilities
COMPONENT_PROJECT_URL =		https://github.com/pypa/distlib
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/58/07/815476ae605bcc5f95c87a62b95e74a1bce0878bc7a3119bc2bf4178f175/distlib-0.3.6.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:14bad2d9b04d3a36127ac97f30b12a19268f211063d8f8ee4f47108896e11b46
COMPONENT_LICENSE =		PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - virtualenv (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
