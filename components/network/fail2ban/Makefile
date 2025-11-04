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
# This file was automatically generated using the following command:
#   $WS_TOOLS/python-integrate-project -d network/fail2ban fail2ban
#

BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		fail2ban
HUMAN_VERSION =			1.1.0
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Daemon to ban hosts that cause multiple authentication errors
COMPONENT_PROJECT_URL =		https://www.fail2ban.org
COMPONENT_ARCHIVE_URL =		\
	https://github.com/fail2ban/fail2ban/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:474fcc25afdaf929c74329d1e4d24420caabeea1ef2e041a267ce19269570bae
COMPONENT_LICENSE =		GPL-2.0-only AND MIT
COMPONENT_LICENSE_FILE =	COPYING

TEST_STYLE = pytest

COMPONENT_CLASSIFICATION=	System/Services
COMPONENT_FMRI =		network/fail2ban

# This is a standalone application.  Since no other Python project depends on
# it we just provide single unversioned package.
SINGLE_PYTHON_VERSION = yes

include $(WS_MAKE_RULES)/common.mk

# Compile Python file(s) at non-default location
COMPONENT_POST_INSTALL_ACTION += $(PYTHON) -mcompileall $(PROTOETCDIR) ;
# Install SMF manifest files.
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -D $(SOURCE_DIR)/files/solaris-svc-fail2ban $(PROTOLIBDIR)/svc/method/svc-fail2ban ;
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -D $(SOURCE_DIR)/files/solaris-fail2ban.xml $(PROTOLIBDIR)/svc/manifest/network/solaris-fail2ban.xml ;
# Remove paths files for other OS's.
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOETCDIR)/fail2ban/paths-arch.conf ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOETCDIR)/fail2ban/paths-debian.conf ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOETCDIR)/fail2ban/paths-fedora.conf ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOETCDIR)/fail2ban/paths-freebsd.conf ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOETCDIR)/fail2ban/paths-opensuse.conf ;
COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOETCDIR)/fail2ban/paths-osx.conf ;
# Add openindiana paths file.
COMPONENT_POST_INSTALL_ACTION += $(INSTALL) -D $(COMPONENT_DIR)/files/paths-openindiana.conf $(PROTO_DIR)/etc/fail2ban/paths-openindiana.conf ;

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
