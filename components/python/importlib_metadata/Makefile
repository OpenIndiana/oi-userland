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
#   $WS_TOOLS/python-integrate-project importlib_metadata
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		importlib_metadata
COMPONENT_VERSION =		5.0.0
COMPONENT_SUMMARY =		importlib_metadata - Read metadata from Python packages
COMPONENT_PROJECT_URL =		https://github.com/python/importlib_metadata
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/7e/ec/97f2ce958b62961fddd7258e0ceede844953606ad09b672fa03b86c453d3/importlib_metadata-5.0.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:da31db32b304314d044d3c12c79bd59e307889b287ad12ff387b3500835fc2ab
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
# - wheel
PYTHON_BOOTSTRAP = yes

# Disable tests because required packages are not available during bootstrap
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# importlib_metadata does not support setup.py build style so we cannot defer
# to it for bootstrapping Python 3.7.  Use 'build' and 'installer' instead
# (because pyproject_installer does not support Python 3.7).  Strictly speaking
# this is not true bootstrap, but since we do not need to bootstrap Python 3.7
# from scratch we can afford this fake bootstrap keeping in mind that Python
# 3.7 should be EOLed in June 2023.
$(BUILD_DIR)/%-3.7/.built:	COMPONENT_BUILD_CMD =		$(PYTHON) -m build
$(BUILD_DIR)/%-3.7/.built:	COMPONENT_BUILD_ARGS =
$(BUILD_DIR)/%-3.7/.built:	COMPONENT_BUILD_ARGS +=		--wheel
$(BUILD_DIR)/%-3.7/.built:	COMPONENT_BUILD_ARGS +=		--no-isolation

$(BUILD_DIR)/%-3.7/.installed:	COMPONENT_INSTALL_CMD =		$(PYTHON) -m installer
$(BUILD_DIR)/%-3.7/.installed:	COMPONENT_INSTALL_ARGS =
$(BUILD_DIR)/%-3.7/.installed:	COMPONENT_INSTALL_ARGS +=	--destdir $(PROTO_DIR)
$(BUILD_DIR)/%-3.7/.installed:	COMPONENT_INSTALL_ARGS +=	$(@D)/dist/*.whl

USERLAND_REQUIRED_PACKAGES += library/python/build-37
USERLAND_REQUIRED_PACKAGES += library/python/installer-37

BOOTSTRAP_TRANSFORMS =

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
