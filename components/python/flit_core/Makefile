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
COMPONENT_VERSION =		3.8.0
COMPONENT_SUMMARY =		flit_core - Distribution-building parts of Flit. See flit package for more information
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/10/e5/be08751d07b30889af130cec20955c987a74380a10058e6e8856e4010afc/flit_core-3.8.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:b305b30c99526df5e63d6022dd2310a0a941a187bd3884f4c8ef0418df6c39f3
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - installer
# - typing_extensions
PYTHON_BOOTSTRAP = yes

# Disable tests because required packages are not available during bootstrap
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# flit_core does not support setup.py build style so we cannot defer to it for
# bootstrapping Python 3.7.  Use 'build' and 'installer' instead (because
# pyproject_installer does not support Python 3.7).  Strictly speaking this is
# not true bootstrap, but since we do not need to bootstrap Python 3.7 from
# scratch we can afford this fake bootstrap keeping in mind that Python 3.7
# should be EOLed in June 2023.
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

# Auto-generated dependencies
