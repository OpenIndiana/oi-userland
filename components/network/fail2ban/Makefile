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

BUILD_STYLE = pyproject
# We need to force the setup.py build style to install files in the proper locations
BUILD_STYLE = setup.py

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		fail2ban
HUMAN_VERSION =			1.1.1
COMPONENT_SUMMARY =		Daemon to ban hosts that cause multiple authentication errors
COMPONENT_PROJECT_URL =		https://www.fail2ban.org
COMPONENT_ARCHIVE_URL =		\
	https://github.com/fail2ban/fail2ban/archive/refs/tags/$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH =	\
	sha256:4be0ea0488e32de260058462a44a040f0542cd26a9fb6fa6d2514f9dd8ec1609
COMPONENT_LICENSE =		GPL-2.0-only AND MIT
COMPONENT_LICENSE_FILE =	COPYING

# This project uses custom testing.  See $(SOURCE_DIR)/RELEASE.
TEST_STYLE = custom

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

# Custom testing
COMPONENT_TEST_CMD = $(PYTHON) bin/fail2ban-testcases
COMPONENT_TEST_ARGS = -vv
COMPONENT_TEST_TARGETS =

# Random temporary directory
COMPONENT_TEST_TRANSFORMS += "-e 's|\(/tmp/monitorfailures_FilterPoll_\).\{8\}\(fail2ban\)|\1XXXXXXXX\2|'"

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES.python += runtime/python
