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
COMPONENT_VERSION=	a4e0163ba69ad3431808bd87a7abd46f8c1bd215
IPS_COMPONENT_VERSION=	0.0.1.20170501
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_VERSION).zip
COMPONENT_SUMMARY=	illumos SMF root certificate service	
COMPONENT_ARCHIVE_URL=  https://github.com/openindiana/smf-cacert/archive/$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= sha256:4292b1ca04b1020aab5316505103b40813ee5e75b7ecc8f33dd2f84d5185df2a
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
