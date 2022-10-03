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
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2022 Niklas Poslovski
#
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		procmail
COMPONENT_VERSION=	3.24
#COMPONENT_REVISION=	4
COMPONENT_PROJECT_URL=	https://github.com/BuGlessRB/procmail
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:514ea433339783e95df9321e794771e4887b9823ac55fdb2469702cf69bd3989
COMPONENT_ARCHIVE_URL=	https://github.com/BuGlessRB/procmail/archive/refs/tags/v$(COMPONENT_VERSION).tar.gz
COMPONENT_FMRI=		mail/procmail
COMPONENT_SUMMARY=	Mail processing program
COMPONENT_DESCRIPTION=	Procmail can be used to create mail-servers, mailing lists, sort your incoming mail into separate folders/files (real convenient when subscribing to one or more mailing lists or for prioritising your mail), preprocess your mail, start any programs upon mail arrival (e.g. to generate different chimes on your workstation for different types of mail) or selectively forward certain incoming mail automatically to someone.
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE= GPLv2+ or Artistic

include $(WS_MAKE_RULES)/common.mk

COMPONENT_BUILD_ARGS += LOCKINGTEST=110

COMPONENT_INSTALL_ARGS +=	BASENAME=$(PROTOUSRDIR)
COMPONENT_INSTALL_ARGS +=	MANDIR=$(PROTOUSRSHAREMANDIR)

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

ASLR_MODE = $(ASLR_ENABLE)

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += RPM_OPT_FLAGS="$(CC_BITS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
