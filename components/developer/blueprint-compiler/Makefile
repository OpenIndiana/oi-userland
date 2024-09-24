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
# Copyright 2024 Geoff Weiss
#

include ../../../make-rules/shared-macros.mk
ENV= /usr/bin/env

COMPONENT_NAME=		blueprint-compiler
COMPONENT_VERSION=	0.14.0
COMPONENT_SUMMARY=	A markup language for GTK user interface files.
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:2be7682be51b6cbd64ab6775ee6d5806bf18c599d503056eaa4e58f1705be22b
COMPONENT_ARCHIVE_URL=	https://gitlab.gnome.org/jwestman/$(COMPONENT_NAME)/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://jwestman.pages.gitlab.gnome.org/blueprint-compiler/
COMPONENT_LICENSE=	LGPLv3
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	Development/GNOME and GTK+
COMPONENT_FMRI=		developer/$(COMPONENT_NAME)

BUILD_STYLE=		meson

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

PYTHON_VENDOR_PACKAGES = /usr/lib/python$(PYVER)/vendor-packages

COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -i 's/env\ python3/python$(PYTHON_VERSION)/' $(PROTOUSRBINDIR)/blueprint-compiler ; 

# Marcel wants files in vendor-packages instead of where python wants to put them by default
COMPONENT_POST_INSTALL_ACTION += \
        $(GSED) -i 's/site-packages/vendor-packages/' $(PROTOUSRBINDIR)/blueprint-compiler ; \
	$(MV) $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/site-packages $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION)/vendor-packages ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
