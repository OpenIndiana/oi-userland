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
COMPONENT_VERSION=	fd7e03f15c6db18ff48df400331e9a3c968d6cc9
COMPONENT_REVISION=	1
IPS_COMPONENT_VERSION=	0.0.1.20170919
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_VERSION).zip
COMPONENT_SUMMARY=	illumos SMF root certificate service	
COMPONENT_ARCHIVE_URL=  https://github.com/openindiana/smf-cacert/archive/$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= sha256:584197c2df06eb3e8dc4e225052f10a98f11be5263480836465c6e0406cb3906
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

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
