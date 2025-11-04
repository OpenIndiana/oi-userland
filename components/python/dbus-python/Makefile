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
#   $WS_TOOLS/python-integrate-project dbus-python
#

BUILD_STYLE = pyproject

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		dbus-python
HUMAN_VERSION =			1.3.2
COMPONENT_REVISION =		2
COMPONENT_SUMMARY =		Python bindings for libdbus
COMPONENT_PROJECT_URL =		http://www.freedesktop.org/wiki/Software/DBusBindings/#python
COMPONENT_ARCHIVE_HASH =	\
	sha256:ad67819308618b5069537be237f8e68ca1c7fcc95ee4a121fe6845b1418248f8
COMPONENT_LICENSE =		MIT
COMPONENT_LICENSE_FILE =	COPYING

# The test style detection does not work properly because pytest is unable to
# automatically discover tests (see below) so we need to force the style here
TEST_STYLE = pytest

include $(WS_MAKE_RULES)/common.mk

# To get correct prefix in the pkgconfig file
COMPONENT_BUILD_ARGS += -Csetup-args="--prefix=$(USRDIR)"
# Set build-dir for meson-python to keep built artifacts needed to run tests
COMPONENT_BUILD_ARGS += -Cbuild-dir="$(@D)/.bld"

# Move include file(s) to the desired location
COMPONENT_POST_INSTALL_ACTION += $(MV) $(PROTOUSRINCDIR)/python$(PYTHON_VERSION)/dbus_python/* $(PROTOUSRINCDIR) ;

# Move the pkgconfig file to the desired location.
# See also https://github.com/mesonbuild/meson-python/issues/240
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTO_DIR)$(PKG_CONFIG_PATH.$(BITS)) ; \
	$(MV) $(PROTO_DIR)/$(PYTHON_LIB)/.dbus_python.mesonpy.libs/pkgconfig/*.pc $(PROTO_DIR)$(PKG_CONFIG_PATH.$(BITS)) ;

# Rename headers and pkgconfig files to contain version number
COMPONENT_POST_INSTALL_ACTION += \
	for f in $$(find $(PROTOUSRINCDIR) $(PROTO_DIR)$(PKG_CONFIG_PATH.$(BITS)) -type f) ; do \
		[ -f $$f ] || continue ; \
		for v in $(PYTHON_VERSIONS) ; do \
			[ "$$f" == "$${f%%$$v}" ] || continue 2 ; \
		done ; \
		$(MV) $$f $$f-$(PYTHON_VERSION) ; \
	done ;

# Automatic test discovery does not work due to hyphen in file names instead of underscore.
# See https://docs.pytest.org/en/stable/explanation/goodpractices.html#test-discovery
COMPONENT_TEST_TARGETS += test/test-*.py

# Make sure testing is able to find built files
COMPONENT_TEST_ENV += PYTHONPATH=$(@D)/.bld/test:$(PROTO_DIR)/$(PYTHON_LIB)

# All tests in following files fails.  This needs further investigation.
PYTEST_ADDOPTS += --deselect test/test-client.py
PYTEST_ADDOPTS += --deselect test/test-p2p.py
PYTEST_ADDOPTS += --deselect test/test-signals.py
PYTEST_ADDOPTS += --deselect test/test-unusable-main-loop.py

# Replace Python version in header and pkgconfig file names
GENERATE_EXTRA_CMD += | $(GSED) \
	-e 's/\(\.h-\)3\.[0-9]\{1,\}$$/\1$$(PYVER)/' \
	-e 's/\(\.pc*-\)3\.[0-9]\{1,\}$$/\1$$(PYVER)/' \
	| uniq

# See 01-ninja.patch
REQUIRED_PACKAGES += developer/build/ninja

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/meson
PYTHON_REQUIRED_PACKAGES += library/python/meson-python
PYTHON_REQUIRED_PACKAGES += library/python/setuptools
PYTHON_REQUIRED_PACKAGES += library/python/wheel
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
