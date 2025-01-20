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

BUILD_STYLE = meson
USE_DEFAULT_TEST_TRANSFORMS = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		blueprint-compiler
COMPONENT_VERSION=	0.16.0
COMPONENT_SUMMARY=	A markup language for GTK user interface files.
COMPONENT_SRC=		$(COMPONENT_NAME)-v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:77a5d593f433c8ca70a05390532cd186c60944cfa6bcd39296c1c2597a7a50fc
COMPONENT_ARCHIVE_URL=	https://gitlab.gnome.org/jwestman/$(COMPONENT_NAME)/-/archive/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://jwestman.pages.gitlab.gnome.org/blueprint-compiler/
COMPONENT_LICENSE=	LGPLv3
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	Development/GNOME and GTK+
COMPONENT_FMRI=		developer/$(COMPONENT_NAME)

include $(WS_MAKE_RULES)/common.mk

# Move all modules from default site-packages directory to vendor-packages
# directory where we place modules shipped by the OS but not included in the
# core Python distribution.
COMPONENT_POST_INSTALL_ACTION += \
	if [ -d $(PROTO_DIR)/$(PYTHON_DIR)/site-packages ] ; then \
		$(RM) -r $(PROTO_DIR)/$(PYTHON_LIB) ; \
		$(MV) $(PROTO_DIR)/$(PYTHON_DIR)/site-packages $(PROTO_DIR)/$(PYTHON_LIB) ; \
	fi ;

# Testing needs an X server
TEST_REQUIRED_PACKAGES += x11/server/xvfb
COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :0 >/dev/null 2>&1 &
COMPONENT_TEST_ENV += DISPLAY=:0
COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

PYTHON_SCRIPTS += usr/bin/blueprint-compiler

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
