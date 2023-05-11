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
#   $WS_TOOLS/python-integrate-project Cython
#

BUILD_STYLE = setup.py
USE_COMMON_TEST_MASTER = no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Cython
HUMAN_VERSION =			0.29.34
COMPONENT_SUMMARY =		Cython - The Cython compiler for writing C extensions for the Python language.
COMPONENT_PROJECT_URL =		http://cython.org/
COMPONENT_ARCHIVE_URL =		\
	https://files.pythonhosted.org/packages/0a/70/1500f05bddb16d795b29fac42954b3c8764c82367b8326c10f038471ae7f/Cython-0.29.34.tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:1909688f5d7b521a60c396d20bba9e47a1b2d2784bfb085401e1e1e7d29a29a8
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	LICENSE.txt

include $(WS_MAKE_RULES)/common.mk

# Our Python 3.7 and Python 3.9 are compiled with removed full path for
# compiler from Python configuration so testing is unable to find proper
# compiler without explicit PATH
COMPONENT_TEST_ENV += PATH="$(GCC_BINDIR):$(PATH)"
# Use well known path for Cython cache directory
COMPONENT_TEST_ENV += CYTHON_CACHE_DIR=$(@D)/.cython-cache-dir

# Normalize tmp dir name
COMPONENT_TEST_TRANSFORMS += "-e 's|\(TEST_TMP/cycache-test\).\{8\}\(/src\).\{8\}/|\1\2/|g'"
# Normalize pointer
COMPONENT_TEST_TRANSFORMS += "-e 's/\(Broken object at \)0x[a-f0-9]\{1,\}>/\1\$$(POINTER)>/g'"
# Remove line with private path
COMPONENT_TEST_TRANSFORMS += "-e '/^libgcov profiling error:/d'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/importlib-metadata
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
