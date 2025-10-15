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
#   $WS_TOOLS/python-integrate-project -d python/coherent.licensed coherent_licensed
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		coherent_licensed
HUMAN_VERSION =			0.5.2
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		License management tooling for Coherent System and skeleton projects
COMPONENT_ARCHIVE_HASH =	\
	sha256:d8071403ce742d3ac3592ddc4fb7057a46caffb415b928b4d52802e5f208416d
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = none

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - zipp
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/flit-core
REQUIRED_PACKAGES.python += runtime/python
