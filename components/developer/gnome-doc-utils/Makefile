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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         gnome-doc-utils
COMPONENT_VERSION=      0.20.10
COMPONENT_REVISION=     5
COMPONENT_SUMMARY=      Documentation utilities for GNOME
COMPONENT_PROJECT_URL=  https://www.gnome.org
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= sha256:cb0639ffa9550b6ddf3b62f3b1add92fb92ab4690d351f2353cffe668be8c4a6
COMPONENT_ARCHIVE_URL=  https://download.gnome.org/sources/$(COMPONENT_NAME)/0.20/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			developer/gnome/gnome-doc-utils
COMPONENT_CLASSIFICATION=	Development/GNOME and GTK+
COMPONENT_LICENSE=		GPLv2, LGPLv2

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Missing files in build dir for xml2po without this.
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

COMPONENT_BUILD_ARGS += V=1

# Move Python modules from site-packages directory to vendor-packages directory
COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTO_DIR)/$(PYTHON_DIR)/site-packages $(PROTO_DIR)/$(PYTHON_LIB) ;

PYTHON_SCRIPTS += usr/bin/xml2po

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
