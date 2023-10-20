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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ruamel.yaml
HUMAN_VERSION =			0.17.39
COMPONENT_SUMMARY =		ruamel.yaml - ruamel.yaml is a YAML parser/emitter that supports roundtrip preservation of comments, seq/map flow style, and map key order
COMPONENT_PROJECT_URL =		https://sourceforge.net/p/ruamel-yaml/code/ci/default/tree
COMPONENT_ARCHIVE_URL =		\
	https://sourceforge.net/projects/ruamel-dl-tagged-releases/files/$(COMPONENT_ARCHIVE)/download
COMPONENT_ARCHIVE_HASH =	\
	sha256:51de3ac8951432bafb09ac968cef25a4075aded223fe2a009a394056d81965eb
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.xz

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/ruamel-yaml-clib
PYTHON_REQUIRED_PACKAGES += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
