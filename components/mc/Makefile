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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		mc
COMPONENT_VERSION=	4.8.17
COMPONENT_PROJECT_URL=	http://www.midnight-commander.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:66d0cb37baaed8ef930f8ad25a634adad4f264eb61820893920ac87b9dfb783b
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)downloads/$(COMPONENT_ARCHIVE)

TPNO=			29317

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=$(USRSHAREDIR)
CONFIGURE_OPTIONS += --libexecdir=$(USRSHAREDIR)
CONFIGURE_OPTIONS += --with-samba
CONFIGURE_OPTIONS += --with-x
CONFIGURE_OPTIONS += --enable-charset
CONFIGURE_OPTIONS += --without-ext2undel
CONFIGURE_OPTIONS += --with-screen=ncurses
CONFIGURE_OPTIONS += --with-ncurses-includes=$(USRINCDIR)
CONFIGURE_OPTIONS += --with-ncurses-libs=$(USRLIBDIR64)
CONFIGURE_OPTIONS += "mc_cv_nroff_tascii="

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libssh2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/ksh93
