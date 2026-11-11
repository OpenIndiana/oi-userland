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
#   $WS_TOOLS/python-integrate-project -d python/PyOpenGL pyopengl
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyopengl
HUMAN_VERSION =			3.1.10
COMPONENT_SUMMARY =		Standard OpenGL bindings for Python
COMPONENT_PROJECT_URL =		https://mcfletch.github.io/pyopengl/
COMPONENT_ARCHIVE_URL =		\
	https://github.com/mcfletch/pyopengl/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:c62c09db3c340647f409df31d06a1b03431a2bf9e3ea6e6c5dd570aa046a5ee6
COMPONENT_LICENSE =		BSD-2-Clause
COMPONENT_LICENSE_FILE =	license.txt

include $(WS_MAKE_RULES)/common.mk

# OpenGL/DLLS holds Windows libraries (freeglut, gle), of no use here
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) -r $(PROTOPYTHONVENDORDIR)/OpenGL/DLLS ;

# EGL cannot initialise on Xvfb (no GPU device)
PYTEST_ADDOPTS += --deselect tests/test_checks.py::test_egl_ext_enumerate
# pygame is not packaged
PYTEST_ADDOPTS += --ignore tests/test_arraydatatype.py
PYTEST_ADDOPTS += --ignore tests/test_core.py
PYTEST_ADDOPTS += --ignore tests/test_evaluators.py
PYTEST_ADDOPTS += --ignore tests/test_glgetactiveuniform.py
PYTEST_ADDOPTS += --ignore tests/test_glgetfloat_leak.py
PYTEST_ADDOPTS += --ignore tests/test_sf2946226.py
PYTEST_ADDOPTS += --ignore tests/test_tess.py
PYTEST_ADDOPTS += --ignore tests/test_textures.py
PYTEST_ADDOPTS += --ignore tests/test_vbo_memusage.py
PYTEST_ADDOPTS += --ignore tests/test_wgl.py
PYTEST_ADDOPTS += --deselect tests/test_checks.py::test_check_egl_pygame
PYTEST_ADDOPTS += --deselect tests/test_checks.py::test_check_leak_on_discontiguous_array
PYTEST_ADDOPTS += --deselect tests/test_checks.py::test_check_init_framebufferarb
PYTEST_ADDOPTS += --deselect tests/test_checks.py::test_feedbackvarying
PYTEST_ADDOPTS += --deselect tests/test_checks.py::test_test_sf2946226
PYTEST_ADDOPTS += --deselect tests/test_checks.py::test_test_glgetactiveuniform
PYTEST_ADDOPTS += --deselect tests/test_checks.py::test_test_glgetfloat_leak
# python-xlib is not packaged
PYTEST_ADDOPTS += --deselect tests/test_checks.py::test_check_egl_es1
PYTEST_ADDOPTS += --deselect tests/test_checks.py::test_check_egl_es2
PYTEST_ADDOPTS += --deselect tests/test_checks.py::test_check_egl_opengl
PYTEST_ADDOPTS += --deselect tests/test_checks.py::test_check_egl_platform_ext
# numpy alters the test results (it is not a test requirement), so make sure
# it is not installed
TEST_CONFLICTING_PACKAGES.python += library/python/numpy

# Testing needs an X server with a 24-bit visual (GLX FBConfigs for GLUT)
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :0 -screen 0 1024x768x24 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Auto-generated dependencies
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/psutil
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
