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
#   $WS_TOOLS/python-integrate-project pydantic_core
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		pydantic_core
HUMAN_VERSION =			2.23.4
COMPONENT_SUMMARY =		Core functionality for Pydantic validation and serialization
COMPONENT_PROJECT_URL =		https://github.com/pydantic/pydantic-core
COMPONENT_ARCHIVE_HASH =	\
	sha256:2584f7cf844ac4d970fba483a717dbe10c1c1c96a969bf65d61ffe94df1b2863
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	LICENSE

TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# https://www.illumos.org/issues/15767
LD_Z_IGNORE=

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIREMENTS += tests/requirements.txt
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark

# Normalize pointers
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{16\}/\$$(POINTER)/g'"
COMPONENT_TEST_TRANSFORMS += "-e 's/0x[0-9a-f]\{12\}/\$$(POINTER)/g'"
# Normalize random uuids
COMPONENT_TEST_TRANSFORMS += "-e 's/\(core_schema_right11-\)[0-9a-f]\{8\}-[0-9a-f]\{4\}-[0-9a-f]\{4\}-[0-9a-f]\{4\}-[0-9a-f]\{12\}/\1\$$(UUID)/g'"
COMPONENT_TEST_TRANSFORMS += "-e 's/\(core_schema_right11-.*\)[0-9a-f]\{8\}-[0-9a-f]\{4\}-[0-9a-f]\{4\}-[0-9a-f]\{4\}-[0-9a-f]\{12\}/\1\$$(UUID)/g'"
# Normalize order of items in lists
COMPONENT_TEST_TRANSFORMS += "-e \"s/{'\([bc]\)', 'a'}/{'a', '\1'}/g\""
COMPONENT_TEST_TRANSFORMS += "-e \"s/{'[abc]', '[abc]', '[abc]'}/{'a', 'b', 'c'}/g\""
COMPONENT_TEST_TRANSFORMS += "-e 's/\"b\(\": SerField.*\"\)a\(\": SerField\)/\"a\1b\2/g'"
COMPONENT_TEST_TRANSFORMS += "-e \"s/\({[12', ]*\)b'3'\([12', ]*}\)/b\1'3'\2/g\""
COMPONENT_TEST_TRANSFORMS += "-e \"s/\({[13', ]*\)'2'\([13', ]*}\)/'\12\2/g\""
COMPONENT_TEST_TRANSFORMS += "-e \"s/\({[12, ]*\)'3'\([12, ]*}\)/\13\2'/g\""
COMPONENT_TEST_TRANSFORMS += "-e 's/{[123], [123], [123]}/{1, 2, 3}/g'"
COMPONENT_TEST_TRANSFORMS += "-e \"s/\({[12, ]*\)3\([12, ]*}\)'/\1'3'\2/g\""
COMPONENT_TEST_TRANSFORMS += "-e \"s/'\({[13', ]*\)2\([13', ]*}\)/\1'2'\2/g\""
COMPONENT_TEST_TRANSFORMS += "-e \"s/b\({[12', ]*\)'3'\([12', ]*}\)/\1b'3'\2/g\""

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/maturin
PYTHON_REQUIRED_PACKAGES += library/python/typing-extensions
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
TEST_REQUIRED_PACKAGES.python += library/python/coverage
TEST_REQUIRED_PACKAGES.python += library/python/dirty-equals
TEST_REQUIRED_PACKAGES.python += library/python/exceptiongroup
TEST_REQUIRED_PACKAGES.python += library/python/hypothesis
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pytest-mock
TEST_REQUIRED_PACKAGES.python += library/python/pytest-timeout
TEST_REQUIRED_PACKAGES.python += library/python/python-dateutil
TEST_REQUIRED_PACKAGES.python += library/python/typing-extensions
TEST_REQUIRED_PACKAGES.python += library/python/tzdata
