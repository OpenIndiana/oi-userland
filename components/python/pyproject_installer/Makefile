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
#   $WS_TOOLS/python-integrate-project pyproject_installer
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyproject_installer
COMPONENT_VERSION =		0.3.0
COMPONENT_SUMMARY =		pyproject_installer - Pyproject installer
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/3c/fa/d5cd59b42e7958526e756ee588effd1593d5c4adbc85fa5a55e0f906a876/pyproject_installer-0.3.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:bcec19bed803d2105b307ab64d779d1f9c75c6799a3fdce35d7ff5f7853d9730
COMPONENT_LICENSE =		MIT

# The pyproject_installer is small, PEP 517 compliant, self contained Python
# project capable to build and install itself and other projects without
# dependency on non-core Python modules.  It will be used to package full
# featured 'build' and 'installer' projects.
PYTHON_BOOTSTRAP = yes

# https://github.com/stanislavlevin/pyproject_installer/issues/13
TEST_STYLE = none

# This project requires Python >= 3.8
PYTHON_VERSIONS = 3.9

include $(WS_MAKE_RULES)/common.mk

# Allow the bootstrapping pyproject_installer to find its own modules
PYTHON_ENV += PYTHONPATH=$(@D)/src

# Special self contained build command for bootstrap
COMPONENT_BUILD_CMD =		$(PYTHON) -m pyproject_installer build
COMPONENT_BUILD_ARGS =

# Special self contained install command for bootstrap
COMPONENT_INSTALL_CMD =		$(PYTHON) -m pyproject_installer install
COMPONENT_INSTALL_ARGS =
COMPONENT_INSTALL_ARGS +=	--destdir $(PROTO_DIR)

# pyproject_installer does not bytecompile after the install.  Since we need
# pyc files we need to force that.
COMPONENT_POST_INSTALL_ACTION +=	$(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_LIB) ;

# Auto-generated dependencies
