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
#   $WS_TOOLS/python-integrate-project pytest-mypy-plugins
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pytest-mypy-plugins
HUMAN_VERSION =			1.11.1
COMPONENT_SUMMARY =		pytest-mypy-plugins - pytest plugin for writing tests for mypy plugins
COMPONENT_PROJECT_URL =		https://github.com/TypedDjango/pytest-mypy-plugins
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/ee/c4/c3ec92eda93509afbd16b14dc85fa665bf16874c3d1340e1c793fafc931a/pytest-mypy-plugins-1.11.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:bba330c9ae81668069f9bcdfaa8af799e7f913eb3bae29113732336a97cbda3b
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

# https://github.com/typeddjango/pytest-mypy-plugins/issues/114
COMPONENT_ARCHIVE_URL =		\
	https://github.com/typeddjango/pytest-mypy-plugins/archive/refs/tags/$(HUMAN_VERSION).tar.gz

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/chevron
PYTHON_REQUIRED_PACKAGES += library/python/decorator
PYTHON_REQUIRED_PACKAGES += library/python/mypy
PYTHON_REQUIRED_PACKAGES += library/python/packaging
PYTHON_REQUIRED_PACKAGES += library/python/pytest
PYTHON_REQUIRED_PACKAGES += library/python/pyyaml
PYTHON_REQUIRED_PACKAGES += library/python/regex
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
