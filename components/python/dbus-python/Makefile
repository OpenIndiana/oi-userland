#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Alexander Pyhalov
# Copyright 2019 Michal Nowak
# Copyright 2022 Gary Mills
# Copyright 2023 Klaus Ziegler
#

BUILD_BITS= 64
BUILD_STYLE= setup.py
TEST_STYLE= pytest
USE_COMMON_TEST_MASTER= yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         dbus-python
COMPONENT_VERSION=      1.3.2
COMPONENT_PROJECT_URL=  https://www.freedesktop.org/wiki/Software/DBusBindings/
COMPONENT_SUMMARY=      Python bindings for D-Bus
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:ad67819308618b5069537be237f8e68ca1c7fcc95ee4a121fe6845b1418248f8
COMPONENT_ARCHIVE_URL=  https://dbus.freedesktop.org/releases/dbus-python/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/python/python-dbus
COMPONENT_CLASSIFICATTION= Development/Python
COMPONENT_LICENSE=      MIT
COMPONENT_LICENSE_FILE= COPYING

PATH=$(PATH.gnu)

include $(WS_MAKE_RULES)/common.mk

PYTHON_ENV += DBUS_PYTHON_USE_AUTOTOOLS=true

# Rename SO files to cpython names
COMPONENT_POST_INSTALL_ACTION += \
	EXT_SUFFIX=$(shell $(PYTHON) -c "import sysconfig; print(sysconfig.get_config_var('EXT_SUFFIX'))") ; \
	$(MV) $(PROTO_DIR)$(PYTHON_LIB)/_dbus_bindings.so $(PROTO_DIR)$(PYTHON_LIB)/_dbus_bindings$$EXT_SUFFIX ; \
	$(MV) $(PROTO_DIR)$(PYTHON_LIB)/_dbus_glib_bindings.so $(PROTO_DIR)$(PYTHON_LIB)/_dbus_glib_bindings$$EXT_SUFFIX ;

# Copy some uninstalled files to make way for symlinks
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRINCDIR)/dbus-1.0/dbus; \
	$(CP) $(SOURCE_DIR)/include/dbus/dbus-python.h \
	$(PROTOUSRINCDIR)/dbus-1.0/dbus/dbus-python.h-$(PYTHON_VERSION) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRLIBDIR64)/pkgconfig; \
	$(GSED) -e 's|^prefix=.*$$|prefix=$(USRDIR)|' \
	$(GSED) -e 's|^Version:.*$$|Version: $(COMPONENT_VERSION)|' \
	$(SOURCE_DIR)/dbus-python.pc.in \
	> $(PROTOUSRLIBDIR64)/pkgconfig/dbus-python.pc-$(PYTHON_VERSION) ;

COMPONENT_TEST_ENV=	PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES)

# Tests require packages: pytest benchmark pyparsing
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)/test
COMPONENT_TEST_CMD=     /usr/bin/pytest-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS=	test-*.py

# Disable test files that have import failures or produce only errors.
COMPONENT_PRE_TEST_ACTION = \
( cd $(COMPONENT_TEST_DIR); \
  for F in test-unusable-main-loop.py test-client.py test-p2p.py \
	test-signals.py test-service.py; \
  do \
    test -f $$F && $(MV) $$F $$F-not; \
    true; \
  done )

COMPONENT_TEST_TRANSFORMER = $(NAWK)
COMPONENT_TEST_TRANSFORMS = "'/passed/ {gsub(\"in.* =*\",\"\"); print $0}'"

# Added test dependencies for all python versions
TEST_REQUIRED_PACKAGES.python += library/python/pytest
TEST_REQUIRED_PACKAGES.python += library/python/pyparsing
TEST_REQUIRED_PACKAGES.python += library/python/pytest-benchmark

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
