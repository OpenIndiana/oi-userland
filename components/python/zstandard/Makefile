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
#   $WS_TOOLS/python-integrate-project zstandard
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		zstandard
HUMAN_VERSION =			0.23.0
COMPONENT_SUMMARY =		Zstandard bindings for Python
COMPONENT_PROJECT_URL =		https://github.com/indygreg/python-zstandard
COMPONENT_ARCHIVE_HASH =	\
	sha256:b2d8c62d08e7255f68f7a740bae85b3c9b8e5466baa9cbf7f57f1cde0ac6bc09
COMPONENT_LICENSE =		BSD-3-Clause
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

#
# Tests are run from build directory that contains cloned copy of sdist.  We
# try to ask Python to find tested modules in the proto area (the PYTHONPATH is
# set accordingly), but Python (< 3.11) always adds the current directory to
# sys.path and there is no known (simple) way how to avoid that.  Except -I,
# but that would cause Python to ignore PYTHONPATH too so we would not have
# access to the proto area either.  The -P option together with PYTHONSAFEPATH
# environment variable were added to Python 3.11 only so we cannot use them yet
# for all Python versions we support.
#
# Since sdist for this project contains the main module in the top-level
# directory we cannot force Python to skip it.  But, unfortunately, this module
# does not contain built dynamic libraries, so Python cannot find them while
# testing.
#
# To workaround this we rename the main module in the build directory during
# testing so Python will need to defer to PYTHONPATH.
#
COMPONENT_PRE_TEST_ACTION +=	$(MV) $(@D)/zstandard $(@D)/zstandard-RENAMED ;
COMPONENT_POST_TEST_ACTION +=	$(MV) $(@D)/zstandard-RENAMED $(@D)/zstandard ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/cffi
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += system/library
