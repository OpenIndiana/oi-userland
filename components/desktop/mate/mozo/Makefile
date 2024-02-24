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
# Copyright 2019 Michal Nowak
# Copyright 2020 Marco van Wieringen
# Copyright (c) 2021 Tim Mooney.  All rights reserved
# Copyright 2021 Andreas Wacknitz
#

MATE_CATEGORY= APP
BUILD_STYLE= meson
include ../../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/mate.mk

COMPONENT_NAME=		mozo
COMPONENT_MJR_VERSION=	1.28
COMPONENT_MNR_VERSION=	0
COMPONENT_SUMMARY=	Simple menu editor for MATE
COMPONENT_ARCHIVE_HASH=	sha256:fe98984ffd6aa8c36d0594bcefdba03de39b42d41e007251680384f3cef44924
COMPONENT_FMRI=		desktop/xdg/menu-editor/mozo
COMPONENT_CLASSIFICATION=	Applications/Configuration and Preferences
COMPONENT_LICENSE= LGPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# Move Python modules from site-packages directory to vendor-packages directory
COMPONENT_POST_INSTALL_ACTION += \
	$(MV) $(PROTO_DIR)/$(PYTHON_DIR)/site-packages $(PROTO_DIR)/$(PYTHON_LIB) ;

PYTHON_SCRIPTS += usr/bin/mozo

# Build requirements
PYTHON_REQUIRED_PACKAGES += library/python/pygobject

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
