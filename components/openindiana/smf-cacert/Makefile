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
# Copyright 2017 Adam Stevko. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		smf-cacert
COMPONENT_VERSION=	86c6ead700dc2aa3acd54733caca95d4697fc6b4
IPS_COMPONENT_VERSION=	0.0.1.20170328
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_VERSION).zip
COMPONENT_SUMMARY=	illumos SMF root certificate service	
COMPONENT_ARCHIVE_URL=  https://github.com/openindiana/smf-cacert/archive/$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= sha256:d3c7d0236d5360d526b073d55b390e1d20e265123255318b6c4807fffd9dc932
COMPONENT_LICENSE=	CDDL
COMPONENT_LICENSE_FILE=	OPENSOLARIS.LICENSE
COMPONENT_PROJECT_URL=	http://openindiana.org
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_FMRI= system/ca-certificates	

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
        $(CLONEY) $(SOURCE_DIR) $(@D)

COMPONENT_BUILD_ARGS += DESTDIR=$(PROTO_DIR)
COMPONENT_INSTALL_ARGS += DESTDIR=$(PROTO_DIR)

build: $(BUILD_32)

install: $(INSTALL_32)
