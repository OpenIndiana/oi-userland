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
#   $WS_TOOLS/python-integrate-project ruamel.yaml
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ruamel.yaml
HUMAN_VERSION =			0.17.31
COMPONENT_SUMMARY =		ruamel.yaml - ruamel.yaml is a YAML parser/emitter that supports roundtrip preservation of comments, seq/map flow style, and map key order
COMPONENT_PROJECT_URL =		https://sourceforge.net/p/ruamel-yaml/code/ci/default/tree
COMPONENT_ARCHIVE_URL =		\
	https://sourceforge.net/projects/ruamel-dl-tagged-releases/files/$(COMPONENT_ARCHIVE)/download
COMPONENT_ARCHIVE_HASH =	\
	sha256:0dabc9ae0ea2255c6ece18e4413b5fb78bc8e69162dc3b57c094ec02637e97a2
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.xz

include $(WS_MAKE_RULES)/common.mk

# Testing fails with the randomly plugin installed
PYTEST_ADDOPTS += -p no:randomly

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/ruamel-yaml-clib
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
