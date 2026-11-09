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
# Copyright 2026 Ignacio Soriano
#

# Laid out as $WS_TOOLS/python-integrate-project -d python/PyOpenGL pyopengl
# generates it (python-integrate-project.conf holds the local additions).
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyopengl
HUMAN_VERSION =			3.1.10
COMPONENT_SUMMARY =		Standard OpenGL bindings for Python
COMPONENT_PROJECT_URL =		https://mcfletch.github.io/pyopengl/
COMPONENT_ARCHIVE_HASH =	\
	sha256:c4a02d6866b54eb119c8e9b3fb04fa835a95ab802dd96607ab4cdb0012df8335
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	license.txt

# The tests need an OpenGL display (GLUT, EGL, pygame)
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
