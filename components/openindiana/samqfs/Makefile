# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2022 Carsten Grzemba
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= samqfs
COMPONENT_VERSION= 5.0.1
BRANCH_VERSION = 2022.0.0.0
# COMPONENT_REVISION= 0
COMPONENT_FMRI= system/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/File System
COMPONENT_PROJECT_URL= https://github.com/cgrzemba/$(COMPONENT_NAME)
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)-$(BRANCH_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/archive/$(COMPONENT_VERSION)-$(BRANCH_VERSION).tar.gz 
COMPONENT_ARCHIVE_HASH= \
	sha256:daf8ba6e0b0650115ee5f633d5ead3004ed6d0711af17ee6e3976946fae4fdd7
COMPONENT_LICENSE= CDDL
COMPONENT_LICENSE_FILE= opt/SUNWsamfs/doc/OPENSOLARIS.LICENSE
COMPONENT_SUMMARY= Storage and Archive Manager File System

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ARGS = DEBUG=no MYSQL_VERSION=mariadb/10.3 SAMQFS_VERSION=$(COMPONENT_VERSION)-$(BRANCH_VERSION)

COMPONENT_INSTALL_ARGS = install DEBUG=no DESTDIR=$(PROTO_DIR) SAMQFS_VERSION=$(COMPONENT_VERSION)-$(BRANCH_VERSION)

build:          $(BUILD_32)

install:          $(INSTALL_32)

# Build dependencies
REQUIRED_PACKAGES += library/python/jinja2

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME)
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += database/mariadb-103/library
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
