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
#   $WS_TOOLS/python-integrate-project flit_core
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		flit_core
HUMAN_VERSION =			3.9.0
COMPONENT_SUMMARY =		flit_core - Distribution-building parts of Flit. See flit package for more information
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/c4/e6/c1ac50fe3eebb38a155155711e6e864e254ce4b6e17fe2429b4c4d5b9e80/flit_core-3.9.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:72ad266176c4a3fcfab5f2930d76896059851240570ce9a98733b658cb786eba
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
# - flit_scm (test bootstrap)
# - installer
# - packaging
# - pathspec (test bootstrap)
# - pyproject_hooks
# - typing_extensions
# - wheel
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
