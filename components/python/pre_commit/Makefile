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
#   $WS_TOOLS/python-integrate-project pre_commit
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pre_commit
HUMAN_VERSION =			3.3.3
COMPONENT_SUMMARY =		pre_commit - A framework for managing and maintaining multi-language pre-commit hooks.
COMPONENT_PROJECT_URL =		https://github.com/pre-commit/pre-commit
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/35/0e/564c71fe3cdf59a4acaaccaea354d066e5d9044eba564dac070bb2075432/pre_commit-3.3.3.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a2256f489cd913d575c145132ae196fe335da32d91a8294b7afe6622335dd023
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

# pre_commit >= 3.0.0 requires Python >= 3.8
PYTHON_VERSIONS := $(filter-out 3.7, $(PYTHON_VERSIONS))

# https://github.com/pre-commit/pre-commit/issues/2609
# https://github.com/pre-commit/pre-commit/issues/2872
TEST_STYLE = none

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cfgv
PYTHON_REQUIRED_PACKAGES += library/python/identify
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/nodeenv
PYTHON_REQUIRED_PACKAGES += library/python/pyyaml
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/virtualenv
PYTHON_REQUIRED_PACKAGES += runtime/python
