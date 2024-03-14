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
# Copyright (c) 2013 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

#
# Warnings!
#
# - This is needed for GIMP 2 only.
# - GIMP 2 is 64 bit only, so we build this 64 bit only too.
#

COMPONENT_NAME=		pygtk2
COMPONENT_VERSION=	2.24.0
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://www.gnome.org
COMPONENT_SUMMARY=	Python bindings for GTK+
COMPONENT_SRC=		pygtk-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:cd1c1ea265bd63ff669e92a2d3c2a88eb26bcd9e5363e0f82c896e649f206912
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/pygtk/2.24/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/python/pygtk2-27
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET=	$(NO_TESTS)

# We build for Python 2.7 so the version cannot be in
# PYTHON_VERSIONS_OBSOLETING.
PYTHON_VERSIONS_OBSOLETING := $(filter-out 2.7, $(PYTHON_VERSIONS_OBSOLETING))

include $(WS_MAKE_RULES)/common.mk

# Python 2.7 paths
PYTHON = /usr/bin/amd64/python2.7
PYTHON_VENDOR_PACKAGES = /usr/lib/python2.7/vendor-packages

# Python settings for configure
CONFIGURE_ENV += PYTHON=$(PYTHON)
CONFIGURE_ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
CONFIGURE_ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)

# Move 64 bit libraries to their proper location
COMPONENT_POST_INSTALL_ACTION += \
	for f in $$($(FIND) $(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES) -name '*.so') ; do \
		$(MKDIR) $$(dirname $$f)/64 ; \
		$(MV) $$f $$(dirname $$f)/64/$$(basename $$f) ; \
	done ;

# Drop compiled files
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) $(PROTOUSRLIBDIR.$(BITS))/pygtk/2.0/demos/*.py{c,o} ; \
	$(RM) $(PROTOUSRLIBDIR.$(BITS))/pygtk/2.0/*.py{c,o} ;

# Build dependencies
REQUIRED_PACKAGES += library/python/pygobject-27

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/libglade
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
