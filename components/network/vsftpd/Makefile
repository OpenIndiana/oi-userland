#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c)  2020 Carsten Grzemba
#

BUILD_BITS=64
BUILD_STYLE=                    justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		vsftpd
COMPONENT_VERSION=	3.0.3
COMPONENT_PROJECT_URL=	https://security.appspot.com/vsftpd.html
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:9d4d2bf6e6e2884852ba4e69e157a2cecd68c5a7635d66a3a8cf8d898c955ef7
COMPONENT_ARCHIVE_URL=https://security.appspot.com/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= LICENSE
COMPONENT_FMRI=                 network/vsftpd
COMPONENT_CLASSIFICATION=       System/Services
COMPONENT_SUMMARY=	FTP server that aims to be very secure

TEST_TARGET=                    $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# IPS_COMPONENT_VERSION is by default set to $(COMPONENT_VERSION) but it is not
# enough for us. We need to include the $(COMPONENT_SUBVERSION) somehow.
# Because the IPS_COMPONENT_VERSION cannot contain letters we used '.0.5'
# instead of 'e'.
IPS_COMPONENT_VERSION=  $(COMPONENT_VERSION)
 
COMPONENT_INSTALL_ACTION = \
	$(INSTALL) -Dpm 755 $(@D)/vsftpd $(PROTO_DIR)$(USRLIBDIR)/inet/vsftpd; \
	$(INSTALL) -Dpm 644 $(@D)/vsftpd.8 $(PROTO_DIR)$(USRSHAREMANDIR)/man8/vsftpd.8; \
	$(INSTALL) -Dpm 644 $(@D)/vsftpd.conf.5 $(PROTO_DIR)$(USRSHAREMANDIR)/man5/vsftpd.conf.5; \
	$(INSTALL) -Dpm 644 $(@D)/vsftpd.conf $(PROTO_DIR)$(ETCDIR)/vsftp/vsftpd-example.conf

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += library/security/openssl
