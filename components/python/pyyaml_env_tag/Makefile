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
#   $WS_TOOLS/python-integrate-project -d python/pyyaml_env_tag pyyaml-env-tag
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pyyaml-env-tag
HUMAN_VERSION =			1.0
COMPONENT_SUMMARY =		A custom YAML tag for referencing environment variables in YAML files.
COMPONENT_PROJECT_URL =		https://github.com/waylan/pyyaml-env-tag
COMPONENT_ARCHIVE_URL =		\
	https://github.com/waylan/pyyaml-env-tag/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:f163e9751c9cc6c0ae0228f40871f133d3fb0f9dc08931c2032f4a33da38d67d
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pyyaml
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
