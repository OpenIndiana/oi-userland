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
HUMAN_VERSION =			5.3.1
COMPONENT_SUMMARY =		jupyter_core - Jupyter core package. A base package on which Jupyter projects rely.
COMPONENT_PROJECT_URL =		https://jupyter.org
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/9e/53/f27bd74ceaa672a1ce17b4b2bee93c0742ca00cb9f540ec4fa60cf7319b5/jupyter_core-5.3.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:5ba5c7938a7f97a6b0481463f7ff0dbac7c15ba48cf46fa4035ca6e838aa1aba
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

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
