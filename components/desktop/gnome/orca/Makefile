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
# Copyright 2024 Marcel Telka
#

BUILD_STYLE = meson

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=			orca
HUMAN_VERSION=			47.2
COMPONENT_SUMMARY=		Screen reader for graphical applications that use the atspi protocol
COMPONENT_ARCHIVE_HASH=		sha256:5e67af357f7198ea00a44381cab4c4f94e6826d6ed800668f39416ce2aab8e5a
COMPONENT_FMRI=			gnome/accessibility/orca
COMPONENT_CLASSIFICATION=	Applications/Universal Access
COMPONENT_LICENSE=		LGPL-2.1-only
COMPONENT_LICENSE_FILE=		COPYING

include $(WS_MAKE_RULES)/gnome.mk
include $(WS_MAKE_RULES)/common.mk

# GNU msgfmt is needed
PATH = $(PATH.gnu)

# Move all modules from default site-packages directory to vendor-packages
# directory where we place modules shipped by the OS but not included in the
# core Python distribution.
COMPONENT_POST_INSTALL_ACTION += \
	if [ -d $(PROTO_DIR)/$(PYTHON_DIR)/site-packages ] ; then \
		$(RM) -r $(PROTO_DIR)/$(PYTHON_LIB) ; \
		$(MV) $(PROTO_DIR)/$(PYTHON_DIR)/site-packages $(PROTO_DIR)/$(PYTHON_LIB) ; \
	fi ;

PYTHON_SCRIPTS += usr/bin/orca

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pygobject
PYTHON_REQUIRED_PACKAGES += runtime/python
