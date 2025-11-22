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
#   $WS_TOOLS/python-integrate-project -d python/Cython cython
#

BUILD_STYLE = pyproject
# Force setup.py build style because with the default PEP 517 build style we
# are unable to generate the list of required packages.
# See also https://github.com/cython/cython/issues/6305
BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		cython
HUMAN_VERSION =			3.1.7
COMPONENT_SUMMARY =		The Cython compiler for writing C extensions in the Python language.
COMPONENT_PROJECT_URL =		https://cython.org/
COMPONENT_ARCHIVE_HASH =	\
	sha256:6f78b9053861325a44468fa4b48f11950635cd6d4715e8cd2633c73dd6a75a3d
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

#
# Following dependency loops were detected (where 'A --> B' means 'A needs B to
# run tests', and 'A ==> B' means 'A needs B for build and/or run'):
#
# Cython --> numpy ==> Cython
#
# To break loops we need to allow this project to integrate without testing in
# a case the required projects are not available yet (bootstrap).
#
PYTHON_TEST_BOOTSTRAP = yes

include $(WS_MAKE_RULES)/common.mk

# Use well known path for Cython cache directory
COMPONENT_TEST_ENV += CYTHON_CACHE_DIR=$(@D)/.cython-cache-dir
# Testing installs packages using pip so direct it to private directory
COMPONENT_TEST_ENV += PYTHONUSERBASE=$(@D)/.python-user-base

# Cleanup remnants from previous test run (if any)
COMPONENT_PRE_TEST_ACTION += $(RM) -r $(@D)/.cython-cache-dir ;
COMPONENT_PRE_TEST_ACTION += $(RM) -r $(@D)/.python-user-base ;

# Normalize tmp dir name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(TEST_TMP/cycache-test\).\{8\}\(/src\).\{8\}/|\1\2/|g'"
COMPONENT_TEST_TRANSFORMS += "-e 's|\(TEST_TMP/recythonize-test\).\{8\}\(/src\).\{8\}/|\1\2/|g'"
# Normalize pointers
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{12\}/\$$(POINTER)/g'"
# Remove profiling info
COMPONENT_TEST_TRANSFORMS += "-e '/^Most expensive pipeline stages:/d'"
# Normalize random file name
COMPONENT_TEST_TRANSFORMS += "-e 's/\(_cython_inline_\).\{64\}\.pyx/\1XXXXXXXX.pyx/'"

# tox.ini does not specify test requirements
TEST_REQUIREMENTS += test-requirements.txt

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/importlib-metadata
REQUIRED_PACKAGES.python += library/python/setuptools
REQUIRED_PACKAGES.python += runtime/python
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/numpy
TEST_REQUIRED_PACKAGES.python += library/python/pycodestyle
TEST_REQUIRED_PACKAGES.python += library/python/setuptools
