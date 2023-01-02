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
#   $WS_TOOLS/python-integrate-project jupyter_core
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		jupyter_core
HUMAN_VERSION =			5.1.1
COMPONENT_SUMMARY =		jupyter_core - Jupyter core package. A base package on which Jupyter projects rely.
COMPONENT_PROJECT_URL =		https://jupyter.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/20/00/2f3c7b30ca75b36588a3d4e203b909bd15e5c70fd449bf1e2b88fabd55ef/jupyter_core-5.1.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f342d29eb6edb06f8dffa69adea987b3a9ee2b6702338a8cb6911516ea0b432d
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	COPYING.md

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Remove unpatched version of files from proto area to make sure they do not
# leak into sample manifest.
COMPONENT_POST_INSTALL_ACTION += \
	$(FIND) $(PROTO_DIR)/$(PYTHON_LIB) -name '*.~*~' -exec rm {} \; ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/platformdirs
PYTHON_REQUIRED_PACKAGES += library/python/traitlets
PYTHON_REQUIRED_PACKAGES += runtime/python
