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
# Copyright (c) Aurelien Larcher. All rights reserved.
#
include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		instant
COMPONENT_VERSION=	1.0.1
COMPONENT_FMRI=		library/python-2/instant
COMPONENT_PROJECT_URL=	https://launchpad.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:283f89cb26ec0b9e1f75c434a7ae1df4d9f688e935160422c5875f214995d4d3
COMPONENT_ARCHIVE_URL=	https://launchpad.net/$(COMPONENT_NAME)/1.0.x/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_BUGDB=	$(COMPONENT_FMRI)
COMPONENT_SUMMARY=	Instant inlining of C and C++ code in Python

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk


COMPONENT_POST_INSTALL_ACTION+=$(CP) $(PROTOUSRBINDIR)/instant-clean $(PROTOUSRBINDIR)/instant-clean$(PYTHON_VERSION);
COMPONENT_POST_INSTALL_ACTION+=$(CP) $(PROTOUSRBINDIR)/instant-showcache $(PROTOUSRBINDIR)/instant-showcache$(PYTHON_VERSION);

# Man files are misplaced at install
COMPONENT_POST_INSTALL_ACTION+=$(MV) -f $(PROTO_DIR)/$(PYTHON_VENDOR_PACKAGES)/share $(PROTOUSRDIR);
COMPONENT_POST_INSTALL_ACTION+=find $(PROTOUSRDIR)/share/man -name \*.gz  -exec gunzip '{}' ';' ;


build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
