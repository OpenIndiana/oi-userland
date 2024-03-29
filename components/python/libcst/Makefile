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
#   $WS_TOOLS/python-integrate-project libcst
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		libcst
HUMAN_VERSION =			1.2.0
COMPONENT_SUMMARY =		libcst - A concrete syntax tree with AST-like properties for Python 3.0 through 3.12 programs.
COMPONENT_ARCHIVE_HASH =	\
	sha256:71dd69fff76e7edaf8fae0f63ffcdbf5016e8cd83165b1d0688d6856aa48186a
COMPONENT_LICENSE =		MIT OR PSF-2.0
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

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
COMPONENT_PRE_TEST_ACTION +=	$(MV) $(@D)/libcst $(@D)/libcst-RENAMED ;
COMPONENT_POST_TEST_ACTION +=	$(MV) $(@D)/libcst-RENAMED $(@D)/libcst ;

# Tests in tests/test_fuzz.py require hypothesmith.  We do not have
# hypothesmith package (yet) so we need to disable those tests.
PYTEST_ADDOPTS += --ignore libcst-RENAMED/tests/test_fuzz.py

# https://github.com/Instagram/LibCST/issues/818
PYTEST_ADDOPTS += --ignore libcst-RENAMED/codegen/tests/test_codegen_clean.py

# Remove extra -RENAMED from test report
COMPONENT_TEST_TRANSFORMS += "-e 's/\(libcst\)-RENAMED/\1/g'"

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pyyaml
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-rust
PYTHON_REQUIRED_PACKAGES += library/python/setuptools-scm
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += library/python/typing-inspect
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
