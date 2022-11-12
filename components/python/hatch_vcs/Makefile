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
COMPONENT_VERSION =		0.2.0
COMPONENT_SUMMARY =		hatch_vcs - Hatch plugin for versioning with your preferred VCS
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ac/13/b3d83564c0cc0f1d45b4ea2a78b87b383a8165797613fedf11f1a7e49b48/hatch_vcs-0.2.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:9913d733b34eec9bb0345d0626ca32165a4ad2de15d1ce643c36d09ca908abff
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - platformdirs (test bootstrap)
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += runtime/python
