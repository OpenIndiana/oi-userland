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
# Copyright (c) 2013, Colin Ellis. All rights reserved.
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
# Copyright (c) 2020, Andreas Wacknitz
#

BUILD_BITS= 32_and_64
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libassuan
COMPONENT_VERSION=	3.0.2
COMPONENT_SUMMARY=	GnuPG IPC implementation library
COMPONENT_DESCRIPTION=	A small library implementing the so-called Assuan protocol, \
						used for interprocess communication between most GnuPG components.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.gnupg.org/related_software/libassuan/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	sha256:d2931cdad266e633510f9970e1a2f346055e351bb19f9b78912475b8074c36f6
COMPONENT_ARCHIVE_URL=	https://www.gnupg.org/ftp/gcrypt/libassuan/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/security/libassuan
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE=	GPLv3, LGPLv2

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV += INSTALL="$(INSTALL)"

CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-silent-rules
CONFIGURE_OPTIONS += --with-gpg-error-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS += --with-pic

COMPONENT_POST_INSTALL_ACTION += $(RM) $(PROTOUSRSHAREDIR)/info/dir ;

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
