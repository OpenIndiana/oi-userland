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
#   $WS_TOOLS/python-integrate-project tomli
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		tomli
HUMAN_VERSION =			2.0.1
COMPONENT_REVISION =		3
COMPONENT_SUMMARY =		tomli - A lil' TOML parser
COMPONENT_PROJECT_URL =		https://github.com/hukkin/tomli
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/c0/3f/d7af728f075fb08564c5949a9c95e44352e23dee646869fa104a3b2060a3/tomli-2.0.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:de526c12914f0c550d15924c62d72abc48d6fe7364aa87328337a31007fe8a4f
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
# - flit_scm (test bootstrap)
# - hatchling (test bootstrap)
# - pep517
# - pytest (test bootstrap)
# - setuptools_scm
# - tox (test bootstrap)
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
