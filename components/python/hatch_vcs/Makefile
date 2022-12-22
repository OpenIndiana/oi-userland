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
#   $WS_TOOLS/python-integrate-project hatch_vcs
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		hatch_vcs
HUMAN_VERSION =			0.3.0
COMPONENT_SUMMARY =		hatch_vcs - Hatch plugin for versioning with your preferred VCS
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/04/33/b68d68e532392d938472d16a03e4ce0ccd749ea31b42d18f8baa6547cbfd/hatch_vcs-0.3.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:cec5107cfce482c67f8bc96f18bbc320c9aa0d068180e14ad317bbee5a153fee
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - platformdirs (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += runtime/python
