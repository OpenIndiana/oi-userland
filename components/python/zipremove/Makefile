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
#   $WS_TOOLS/python-integrate-project zipremove
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zipremove
HUMAN_VERSION =			0.10.0
COMPONENT_SUMMARY =		Extend \`zipfile\` with remove-related capabilities
COMPONENT_PROJECT_URL =		https://github.com/danny0838/zipremove
COMPONENT_ARCHIVE_HASH =	\
	sha256:3c5957c115447b54299d3a23128764b59c4558fc98c4b878ff2dbc5db8a62021
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE.txt

# We do not need zipremove for Python 3.9
PYTHON_VERSIONS := $(filter-out 3.9,$(PYTHON_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# https://github.com/danny0838/zipremove/issues/1
COMPONENT_POST_UNPACK_ACTION += $(TOUCH) $(SOURCE_DIR)/tests/__init__.py

# Force verbose output via tox posargs
TOX_POSARGS += -v

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += library/python/wheel
REQUIRED_PACKAGES.python += runtime/python
