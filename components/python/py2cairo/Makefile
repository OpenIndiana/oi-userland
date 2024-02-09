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
# - This must stay forever at version 1.8.x.
# - GIMP 2 is 64 bit only, so we build this 64 bit only too.
#

COMPONENT_NAME=		py2cairo
COMPONENT_VERSION=	1.8.10
COMPONENT_PROJECT_URL=	http://www.cairographics.org
COMPONENT_SUMMARY=	Python bindings for Cairo
COMPONENT_SRC=		pycairo-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:b15f71019e42e06d86f7e8fe5587f07c3de5a59a6c3a071b25fe100796dbcd56
COMPONENT_ARCHIVE_URL=	http://cairographics.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/python/pycairo-27
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	LGPL-2.1-only
COMPONENT_LICENSE_FILE=	COPYING-LGPL-2.1

TEST_TARGET=	$(NO_TESTS)

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

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += system/library
