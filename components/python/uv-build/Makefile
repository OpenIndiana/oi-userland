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
#   $WS_TOOLS/python-integrate-project -d python/uv-build uv_build
#

BUILD_STYLE = pyproject
CARGO_VENDOR = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		uv_build
HUMAN_VERSION =			0.11.15
COMPONENT_SUMMARY =		The uv build backend
COMPONENT_PROJECT_URL =		https://pypi.org/project/uv/
COMPONENT_ARCHIVE_HASH =	\
	sha256:21aa244bced4e9cbf0dfe01a43758299b8bad76033254e48701295cd13466e28
COMPONENT_LICENSE =		Apache-2.0 OR MIT

# https://github.com/astral-sh/uv/issues/16849
TEST_STYLE = custom

include $(WS_MAKE_RULES)/common.mk

# https://github.com/astral-sh/uv/issues/16849
COMPONENT_TEST_CMD = $(CARGO) test
COMPONENT_TEST_ARGS += --release
COMPONENT_TEST_ARGS += --offline
COMPONENT_TEST_ARGS += -p uv-build-backend
COMPONENT_TEST_TARGETS =

# skip failing tests
# see https://github.com/astral-sh/uv/issues/16849
COMPONENT_TEST_ARGS += --
COMPONENT_TEST_ARGS += --skip tests::built_by_uv_building
COMPONENT_TEST_ARGS += --skip wheel::test::test_prepare_metadata

# drop header
COMPONENT_TEST_TRANSFORMS += "-e '0,/Finished/d'"
# remove timing
COMPONENT_TEST_TRANSFORMS += "-e 's/\(finished\) in [0-9]\{1,\}\.[0-9]\{2\}s\$$/\1/g'"
# normalize variable hash in filename
COMPONENT_TEST_TRANSFORMS += "-e 's/\(Running .* (.*-\)[0-9a-f]\{16\})/\1XXXXXXXXXXXXXXXX)/'"
# sort tests
COMPONENT_TEST_TRANSFORMS += "| ( while true ; do \
		$(GSED) -u -e '/^running [0-9]\{1,\} tests\$$/q1' && break ; \
		$(GSED) -u -e '/^\$$/Q' | $(SORT) ; \
		echo "" ; \
	done ) | $(COMPONENT_TEST_TRANSFORMER) -e ''"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES.python += library/python/maturin
REQUIRED_PACKAGES.python += runtime/python
