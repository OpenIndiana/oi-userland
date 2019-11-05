#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

# 
# Copyright 2013, Adam Stevko. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		nicstat
COMPONENT_VERSION=	1.95
COMPONENT_GIT_REV=	1fbe281
COMPONENT_LICENSE=	The Artistic License 2.0
COMPONENT_SRC=		scotte-nicstat-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz	
COMPONENT_ARCHIVE_HASH= sha256:0c441c85af6cace24254f6c1ce21cb1447e13ff7c83582b387c11fc338cc57e4
COMPONENT_PROJECT_URL=	https://github.com/scotte/nicstat/
COMPONENT_ARCHIVE_URL= 	https://codeload.github.com/scotte/nicstat/legacy.tar.gz/$(COMPONENT_GIT_REV)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL=0

COMPONENT_PRE_BUILD_ACTION= $(CP) $(SOURCE_DIR)/Makefile.Solaris $(@D)/Makefile

COMPONENT_BUILD_ENV = CC="$(CC)" 
COMPONENT_BUILD_ARGS = CFLAGS="-m$(BITS)" 

build:         $(BUILD_32_and_64)

install:       $(BUILD_32_and_64)
		$(MKDIR) $(PROTOUSRBINDIR)
		$(MKDIR) $(PROTOUSRBINDIR64)
		$(MKDIR) $(PROTOUSRSHAREMAN1MDIR) 
		$(INSTALL) $(BUILD_DIR_32)/nicstat $(PROTOUSRBINDIR)/nicstat
		$(INSTALL) $(BUILD_DIR_64)/nicstat $(PROTOUSRBINDIR64)/nicstat
		$(INSTALL) $(BUILD_DIR_32)/nicstat.1 $(PROTOUSRSHAREMAN1MDIR)/nicstat.1m
		$(TOUCH) $(BUILD_DIR_32)/.installed
		$(TOUCH) $(BUILD_DIR_64)/.installed

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
