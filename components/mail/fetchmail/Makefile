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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright 2018, Michal Nowak
# Copyright 2021, Nona Hansel
#

USE_OPENSSL11= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fetchmail
COMPONENT_VERSION=	6.4.35
COMPONENT_SUMMARY=	fetch mail from a POP, IMAP, ETRN, or ODMR-capable server
COMPONENT_DESCRIPTION=	Fetchmail is a full-featured, robust, well-documented remote-mail retrieval and forwarding utility intended \
to be used over on-demand TCP/IP links (such as SLIP or PPP connections). It supports every remote-mail protocol now in use on \
	the Internet: POP2, POP3, RPOP, APOP, KPOP, all flavors of IMAP, ETRN, and ODMR. It can even support IPv6 and IPsec.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:7b0b56cbc0fca854504f167795fab532d5a54d5a7d3b6e3e36a33f34a0960a01
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/$(COMPONENT_NAME)/files/branch_6.4/$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz/download 
COMPONENT_PROJECT_URL=	https://www.fetchmail.info/
COMPONENT_FMRI=		mail/fetchmail
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/common.mk

# Change the shebang line to use our default Python version explicitly, drop the fixed file into /usr/bin,
# where our package manifest expects it, and remove the superfluous script from the site-packages folder.
COMPONENT_POST_INSTALL_ACTION = \
	$(GSED) -e "s|/usr/bin/env python|$(PYTHON)|" \
	$(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/fetchmailconf.py > \
	$(PROTOUSRBINDIR)/fetchmailconf && \
	$(RM) $(PROTO_DIR)/usr/lib/python$(PYTHON_VERSION)/site-packages/fetchmailconf.py

CONFIGURE_OPTIONS += --with-kerberos5
CONFIGURE_OPTIONS += --with-ssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += --enable-NTLM

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += system/library
