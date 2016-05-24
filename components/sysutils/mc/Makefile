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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mc
COMPONENT_VERSION=	4.8.17
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.midnight-commander.org/
COMPONENT_SUMMARY=	The GNU Midnight Commander file manager
COMPONENT_DESCRIPTION=	GNU Midnight Commander is a full-screen text mode application that allows user to copy, move and delete files and whole directory trees, search for files and run commands in the subshell
COMPONENT_FMRI=		file/mc
COMPONENT_CLASSIFICATION=	org.opensolaris.category.2008:Desktop (GNOME)/File Managers
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0447bdddc0baa81866e66f50f9a545d29d6eebb68b0ab46c98d8fddd2bf4e44d
COMPONENT_ARCHIVE_URL=	http://ftp.midnight-commander.org/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/mc
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	mc.license


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk


CONFIGURE_SYSCONFDIR=/usr/share
CONFIGURE_LIBEXECDIR.$(BITS)=/usr/share

CONFIGURE_OPTIONS += --with-samba
CONFIGURE_OPTIONS += --with-x
CONFIGURE_OPTIONS += --enable-charset
CONFIGURE_OPTIONS += --without-ext2undel
CONFIGURE_OPTIONS += --with-screen=slang
CONFIGURE_OPTIONS += --enable-vfs-sftp=no
CONFIGURE_OPTIONS += "mc_cv_nroff_tascii="

# Enable Address Space Layout Randomization
ASLR_MODE = $(ASLR_ENABLE)

$(INSTALL_32):	$(INSTALL_64)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/slang
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += system/library
