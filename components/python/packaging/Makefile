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
#   $WS_TOOLS/python-integrate-project packaging
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		packaging
HUMAN_VERSION =			23.1
COMPONENT_SUMMARY =		packaging - Core utilities for Python packages
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/b9/6c/7c6658d258d7971c5eb0d9b69fa9265879ec9a9158031206d47800ae2213/packaging-23.1.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:a392980d2b6cffa644431898be54b0045151319d1e7ec34f0cfed48767dd334f
COMPONENT_LICENSE =		Apache-2.0 OR BSD-2-Clause

TEST_STYLE = pytest

# This component is required by following bootstrapped components so it must be
# bootstrapped too.
# - build
# - hatchling (test bootstrap)
# - pyproject_api (test bootstrap)
# - pytest (test bootstrap)
# - setuptools_scm
# - tox (test bootstrap)
# - Userland build framework (see setup.py.mk)
PYTHON_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/flit-core
PYTHON_REQUIRED_PACKAGES += runtime/python
