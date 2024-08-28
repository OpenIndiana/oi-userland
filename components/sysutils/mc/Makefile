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
# Copyright (c) 2020, Michal Nowak
#

USE_DEFAULT_TEST_TRANSFORMS = yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mc
COMPONENT_VERSION=	4.8.32
COMPONENT_SUMMARY=	The GNU Midnight Commander file manager
COMPONENT_DESCRIPTION=	GNU Midnight Commander is a full-screen text mode application that allows user to copy, move and delete files and whole directory trees, search for files and run commands in the subshell
COMPONENT_PROJECT_URL=	https://www.midnight-commander.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/MidnightCommander/mc/archive/refs/tags/$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:5b8e6a66b53f67a430296e3e490c00af17cbbb449f6c56f406ff02a11d516ba1
COMPONENT_FMRI=		file/mc
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/File Managers
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	doc/COPYING

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) ; $(CONFIG_SHELL) autogen.sh )

CONFIGURE_OPTIONS += --sysconfdir=$(USRSHAREDIR)
CONFIGURE_OPTIONS += --libexecdir=$(USRSHAREDIR)
CONFIGURE_OPTIONS += --with-x
CONFIGURE_OPTIONS += --enable-charset
CONFIGURE_OPTIONS += --disable-vfs-undelfs
CONFIGURE_OPTIONS += --with-screen=slang
CONFIGURE_OPTIONS += --enable-vfs-sftp=no
CONFIGURE_OPTIONS += "mc_cv_nroff_tascii="

# pkgdepend doesn't like the first line of a Python script to be:
# '#!/usr/bin/python' or '#!/usr/bin/env python'so turn it into '#!/usr/bin/python$(PYTHON_VERSION)'
COMPONENT_POST_INSTALL_ACTION += \
    $(GSED) -i -e 's?\/usr\/bin\/python?\/usr\/bin\/python$(PYTHON_VERSION)?' \
    $(PROTO_DIR)/usr/share/mc/extfs.d/s3+ ; \
    $(GSED) -i -e 's?\/usr\/bin\/env python?\/usr\/bin\/python$(PYTHON_VERSION)?' \
    $(PROTO_DIR)/usr/share/mc/extfs.d/uc1541 ;

# Manually added dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python

# Needed for tests
TEST_REQUIRED_PACKAGES += developer/check

# Auto-generated dependencies
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/slang
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += sysutils/e2fsprogs
