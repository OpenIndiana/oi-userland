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
#   $WS_TOOLS/python-integrate-project -d developer/meson meson
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		meson
HUMAN_VERSION =			1.7.0
COMPONENT_SUMMARY =		A high performance build system
COMPONENT_PROJECT_URL =		https://mesonbuild.com
COMPONENT_ARCHIVE_HASH =	\
	sha256:08efbe84803eed07f863b05092d653a9d348f7038761d900412fddf56deb0284
COMPONENT_LICENSE =		Apache-2.0
COMPONENT_LICENSE_FILE =	COPYING

# Manifest options for developer/build/meson package
COMPONENT_FMRI.meson-meta =		developer/build/meson
COMPONENT_CLASSIFICATION.meson-meta =	Development/Distribution Tools

TEST_STYLE = custom

include $(WS_MAKE_RULES)/common.mk

# We have no polkit
COMPONENT_POST_INSTALL_ACTION += $(RM) -r $(PROTOUSRSHAREDIR)/polkit-1 ;

# Rename section 1 man page(s) to contain version number
COMPONENT_POST_INSTALL_ACTION += \
	for f in $(PROTOUSRSHAREMAN1DIR)/*.1 ; do \
		[[ -f $$f ]] || continue ; \
		for v in $(PYTHON_VERSIONS) ; do \
			[[ "$$f" == "$${f%%$$v.1}" ]] || continue 2 ; \
		done ; \
		$(MV) $$f $${f%%.1}-$(PYTHON_VERSION).1 ; \
	done ;

# Custom test style
# See also: https://mesonbuild.com/MesonCI.html
COMPONENT_TEST_CMD = $(PYTHON) run_tests.py
COMPONENT_TEST_ARGS =
COMPONENT_TEST_ARGS += -v		# verbose
COMPONENT_TEST_ARGS += --failfast
COMPONENT_TEST_TARGETS =
COMPONENT_TEST_ENV += PYTEST_ADDOPTS="$(PYTEST_ADDOPTS)"
# Testing expects GNU msgfmt and GNU make
COMPONENT_TEST_ENV += PATH="$(PATH.gnu)"
# Testing needs to find Qt5/Qt6 libraries
COMPONENT_TEST_ENV += LD_LIBRARY_PATH=$(QT5_LIBDIR):$(QT6_LIBDIR)

# Exhausts memory
PYTEST_ADDOPTS += --deselect unittests/linuxliketests.py::LinuxlikeTests::test_generate_gir_with_address_sanitizer
# Uses valgrind and fails (needs further investigation)
PYTEST_ADDOPTS += --deselect unittests/allplatformstests.py::AllPlatformTests::test_testsetups
# Python 2 test that fails in our environment
PYTEST_ADDOPTS += --deselect unittests/machinefiletests.py::NativeFileTests::test_python_module

# Remove timing
COMPONENT_TEST_TRANSFORMS += "-e '/^Total .*time:/d'"

# This project does not support tox so we need to provide test requirements
# manually.
TEST_REQUIRED_PACKAGES.python += library/python/pytest-xdist

# Manually added test dependencies to make sure we test as much as possible and
# to get consistent test results
TEST_REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
TEST_REQUIRED_PACKAGES += library/c++/hdf5
TEST_REQUIRED_PACKAGES += library/qt5
TEST_REQUIRED_PACKAGES += library/qt6

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
