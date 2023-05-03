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

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		ruamel.yaml
HUMAN_VERSION =			0.17.22
COMPONENT_SUMMARY =		ruamel.yaml - ruamel.yaml is a YAML parser/emitter that supports roundtrip preservation of comments, seq/map flow style, and map key order
COMPONENT_PROJECT_URL =		https://sourceforge.net/p/ruamel-yaml/code/ci/default/tree
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/eb/a4/e056a6f778bfc01d653dd777e5ff57c1f1b48fcaa889d75bac0ef9650768/ruamel.yaml-0.17.22.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:c22ec58aaca5105f771cb8f7ac45ad631b5e8b00454ebe1822d442fb696e9e62
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# https://sourceforge.net/p/ruamel-yaml/tickets/403/
# https://sourceforge.net/p/ruamel-yaml/tickets/413/
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/ruamel-yaml-clib
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
