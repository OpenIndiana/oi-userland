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
#   $WS_TOOLS/python-integrate-project prettytable
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		prettytable
HUMAN_VERSION =			3.6.0
COMPONENT_SUMMARY =		prettytable - A simple Python library for easily displaying tabular data in a visually appealing ASCII table format
COMPONENT_PROJECT_URL =		https://github.com/jazzband/prettytable
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ba/b6/8e78337766d4c324ac22cb887ecc19487531f508dbf17d922b91492d55bb/prettytable-3.6.0.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:2e0026af955b4ea67b22122f310b90eae890738c08cb0458693a49b6221530ac
COMPONENT_LICENSE =		BSD-3-Clause

include $(WS_MAKE_RULES)/common.mk

# Remove unpatched version of files from proto area to make sure they do not
# leak into sample manifest.
COMPONENT_POST_INSTALL_ACTION += \
	$(FIND) $(PROTO_DIR)/$(PYTHON_LIB) -name '*.~*~' -exec rm {} \; ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/hatch-vcs
PYTHON_REQUIRED_PACKAGES += library/python/hatchling
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/wcwidth
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-cov
TEST_REQUIRED_PACKAGES.python += library/python/pytest-lazy-fixture
