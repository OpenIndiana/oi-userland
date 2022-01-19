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
#

BUILD_BITS=		64
BUILD_STYLE=		setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dbus-python
COMPONENT_VERSION=	1.2.18
COMPONENT_PROJECT_URL=	https://www.freedesktop.org/wiki/Software/DBusBindings/
COMPONENT_SUMMARY=	Python bindings for D-Bus
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:92bdd1e68b45596c833307a5ff4b217ee6929a1502f5341bae28fd120acf7260
COMPONENT_ARCHIVE_URL=	https://dbus.freedesktop.org/releases/dbus-python/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/python/python-dbus
COMPONENT_CLASSIFICATTION= Development/Python
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	COPYING

PATH=$(PATH.gnu)

PYTHON_VERSIONS = $(PYTHON3_VERSIONS)

include $(WS_MAKE_RULES)/common.mk

# Rename SO files to cpython names
CPIA.3.5 = ( cd $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES) && \
	$(MV) _dbus_bindings.so _dbus_bindings.cpython-35m.so && \
	$(MV) _dbus_glib_bindings.so _dbus_glib_bindings.cpython-35m.so ) ;
CPIA.3.7 = ( cd $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES) && \
	$(MV) _dbus_bindings.so _dbus_bindings.cpython-37m.so && \
	$(MV) _dbus_glib_bindings.so _dbus_glib_bindings.cpython-37m.so ) ;
CPIA.3.9 = ( cd $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES) && \
	$(MV) _dbus_bindings.so _dbus_bindings.cpython-39.so && \
	$(MV) _dbus_glib_bindings.so _dbus_glib_bindings.cpython-39.so ) ;
COMPONENT_POST_INSTALL_ACTION += $(CPIA.$(PYTHON_VERSION))

PREFIX=		     build/amd64-$(PYTHON_VERSION)/temp.solaris-2.11-i86pc.64bit-$(PYTHON_VERSION)/prefix

# Copy some uninstalled files to make way for symlinks
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRINCDIR)/dbus-1.0/dbus; \
	$(CP) $(PREFIX)/include/dbus-1.0/dbus/dbus-python.h \
	$(PROTOUSRINCDIR)/dbus-1.0/dbus/dbus-python.h-$(PYTHON_VERSION) ;
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRLIBDIR)/pkgconfig; \
	$(MKDIR) $(PROTOUSRLIBDIR)/$(MACH64)/pkgconfig; \
	$(GSED) -e 's|^prefix=.*$$|prefix=$(USRDIR)|' \
	$(PREFIX)/lib/pkgconfig/dbus-python.pc \
	> $(PROTOUSRLIBDIR)/pkgconfig/dbus-python.pc-$(PYTHON_VERSION) ;

COMPONENT_TEST_ENV=	PYTHONPATH=$(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES)

# Tests require packages: pytest benchmark pyparsing
COMPONENT_TEST_DIR=	$(COMPONENT_SRC)/test
COMPONENT_TEST_CMD=     /usr/bin/pytest-$(PYTHON_VERSION)
COMPONENT_TEST_ARGS=	test-*.py

# Disable test files that have import failures or produce only errors.
COMPONENT_PRE_TEST_ACTION = \
( cd $(COMPONENT_TEST_DIR); \
  for F in test-unusable-main-loop.py test-client.py test-p2p.py \
	test-signals.py test-exception-py2.py; \
  do \
    test -f $$F && $(MV) $$F $$F-not; \
    true; \
  done )

# Typical results for test target:
#============================= test session starts ===========================
#...
#=============================== warnings summary ============================
#...
#======================== 38 passed, 4 warnings in 0.27s =====================

# Added run-time dependencies
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += runtime/python-39

# Added test dependencies for all python versions
REQUIRED_PACKAGES += library/python/pytest-35
REQUIRED_PACKAGES += library/python/pytest-37
REQUIRED_PACKAGES += library/python/pytest-39
REQUIRED_PACKAGES += library/python/pytest-benchmark-35
REQUIRED_PACKAGES += library/python/pytest-benchmark-37
REQUIRED_PACKAGES += library/python/pytest-benchmark-39
REQUIRED_PACKAGES += library/python/pyparsing-35
REQUIRED_PACKAGES += library/python/pyparsing-37
REQUIRED_PACKAGES += library/python/pyparsing-39

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
