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
# Copyright 2013-2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

#
# Warnings!
#
# - This is needed for GIMP 2 only.
# - This must stay forever at version 2.28.x.
# - GIMP 2 is 64 bit only, so we build this 64 bit only too.
#

COMPONENT_NAME=		pygobject
COMPONENT_VERSION=	2.28.7
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://www.gnome.org
COMPONENT_SUMMARY=	Python bindings for GObject
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:bb9d25a3442ca7511385a7c01b057492095c263784ef31231ffe589d83a96a5a
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/$(COMPONENT_NAME)/2.28/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/python/$(COMPONENT_NAME)-27
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=	$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Python 2.7 paths
PYTHON = /usr/bin/amd64/python2.7
PYTHON_VENDOR_PACKAGES = /usr/lib/python2.7/vendor-packages

# Python settings for configure
CONFIGURE_ENV += PYTHON=$(PYTHON)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)

# Disable libffi support
CONFIGURE_OPTIONS += --without-ffi

# Move 64 bit libraries to their proper location
COMPONENT_POST_INSTALL_ACTION += \
	for f in $$($(FIND) $(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES) -name '*.so') ; do \
		$(MKDIR) $$(dirname $$f)/64 ; \
		$(MV) $$f $$(dirname $$f)/64/$$(basename $$f) ; \
	done ;

# Drop compiled files
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) $(PROTO_DIR)/usr/share/pygobject/2.0/codegen/*.py{c,o} ;

# Manually added dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gobject/gobject-introspection
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
