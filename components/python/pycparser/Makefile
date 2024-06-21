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
#   $WS_TOOLS/python-integrate-project pycparser
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pycparser
HUMAN_VERSION =			2.22
COMPONENT_SUMMARY =		pycparser - C parser in Python
COMPONENT_PROJECT_URL =		https://github.com/eliben/pycparser
COMPONENT_ARCHIVE_HASH =	\
	sha256:491c8be9c040f5390f5bf44a5b07752bd07f56edf992381b05c701439eec10f6
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Due to a packaging oversight, pycparser modifies c_ast.py after
# the compilation is done, resulting in a stale pyc file.
COMPONENT_POST_INSTALL_ACTION += \
	$(PYTHON) -m compileall $(PROTO_DIR)$(PYTHON_LIB)/pycparser/c_ast.py

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
