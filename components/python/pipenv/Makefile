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
#   $WS_TOOLS/python-integrate-project pipenv
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pipenv
HUMAN_VERSION =			2024.4.1
COMPONENT_SUMMARY =		Python Development Workflow for Humans.
COMPONENT_PROJECT_URL =		https://github.com/pypa/pipenv
COMPONENT_ARCHIVE_URL =		\
	https://github.com/pypa/pipenv/archive/refs/tags/v$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:23ba41983863ba157f8cefc45daeca0a11b661a277bbccb3ec065b7d2b3d68c6
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Remove misplaced docs and examples files
# https://github.com/pypa/pipenv/issues/5937
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) -r $(PROTO_DIR)/$(PYTHON_LIB)/docs ; \
	$(RM) -r $(PROTO_DIR)/$(PYTHON_LIB)/examples ;

# https://github.com/pypa/pipenv/issues/6294#issuecomment-2537370184
PYTEST_ADDOPTS += -m "not cli and not needs_internet" tests/unit/

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/certifi
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/virtualenv
PYTHON_REQUIRED_PACKAGES += runtime/python
