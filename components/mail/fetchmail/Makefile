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

BUILD_BITS= 64
USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fetchmail
COMPONENT_VERSION=	6.4.24
COMPONENT_DESCRIPTION=	Full-featured, robust, well-documented remote-mail retrieval and forwarding utility
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:9c961df25cd922f539218b0b56a77e7a47778e49ed907edaa5b4941ad3b253cf
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/$(COMPONENT_NAME)/files/branch_6.4/$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz/download 
COMPONENT_PROJECT_URL=	https://www.fetchmail.info/
COMPONENT_FMRI=		mail/fetchmail

TEST_TARGET=	$(TEST_64)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS  +=		--with-kerberos5
# configure detects OpenSSL 1.0 despite USE_OPENSSL11 being set
CONFIGURE_OPTIONS  +=		--with-ssl=/usr/openssl/1.1/
CONFIGURE_OPTIONS  +=		--enable-NTLM

# Block the fetchmailconf build - this option is taken from configure.ac
CONFIGURE_ENV += PYTHON=:

COMPONENT_TEST_TRANSFORMS= \
	'-e "s/^\# //" ' \
	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/PASS/p" '  \
	'-e "/SKIP/p" '  \
	'-e "/XFAIL/p" ' \
	'-e "/FAIL/p" '  \
	'-e "/XPASS/p" ' \
	'-e "/ERROR/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += system/library
