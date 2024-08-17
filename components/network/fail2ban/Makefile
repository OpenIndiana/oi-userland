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

BUILD_STYLE = setup.py
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= fail2ban
COMPONENT_VERSION= 1.1.0
COMPONENT_SUMMARY= Ban hosts that cause multiple authentication errors
COMPONENT_PROJECT_URL= https://www.fail2ban.org
COMPONENT_FMRI= network/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Services
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= https://github.com/fail2ban/fail2ban/archive/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:474fcc25afdaf929c74329d1e4d24420caabeea1ef2e041a267ce19269570bae
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE=	COPYING

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_CMD = $(PYTHON) setup.py build
COMPONENT_INSTALL_CMD = $(PYTHON) setup.py install
COMPONENT_INSTALL_ARGS += --prefix=/usr
COMPONENT_INSTALL_ARGS += --root=$(PROTO_DIR)
COMPONENT_INSTALL_ARGS += --skip-build

# Install SMF manifest files. Remove paths files for other OS's. 
# Add openindiana paths file.
COMPONENT_POST_INSTALL_ACTION += \
	$(PYTHON) -mcompileall $(PROTO_DIR) ; \
	$(MKDIR) $(PROTO_DIR)/lib/svc/method ; \
	$(CP) $(SOURCE_DIR)/files/solaris-svc-fail2ban $(PROTO_DIR)/lib/svc/method/svc-fail2ban ; \
	$(MKDIR) $(PROTO_DIR)/lib/svc/manifest/network ; \
	$(CP) $(SOURCE_DIR)/files/solaris-fail2ban.xml $(PROTO_DIR)/lib/svc/manifest/network ; \
	$(CP) $(COMPONENT_DIR)/files/paths-openindiana.conf $(PROTO_DIR)/etc/fail2ban ; \
	rm -f $(PROTO_DIR)/etc/fail2ban/paths-arch.conf ; \
	rm -f $(PROTO_DIR)/etc/fail2ban/paths-debian.conf ; \
	rm -f $(PROTO_DIR)/etc/fail2ban/paths-fedora.conf ; \
	rm -f $(PROTO_DIR)/etc/fail2ban/paths-freebsd.conf ; \
	rm -f $(PROTO_DIR)/etc/fail2ban/paths-opensuse.conf ; \
	rm -f $(PROTO_DIR)/etc/fail2ban/paths-osx.conf ; 

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
