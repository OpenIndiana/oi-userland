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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		meld
COMPONENT_VERSION=	1.8.6
COMPONENT_REVISION=	3
COMPONENT_FMRI=		developer/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	meld - graphical diff and merge tool
COMPONENT_DESCRIPTION=\
Meld is a visual diff and merge tool. You can compare two or three files \
and edit them in place (diffs update dynamically). You can compare two or \
three folders and launch file comparisons. You can browse and view a working \
copy from popular version control systems such such as Git, CVS, Subversion, \
Bazaar-ng and Mercurial.
COMPONENT_PROJECT_URL=	http://meld.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:af96682b8f4bf3ad4221c853b1516218d62a17ff43c38f4a83e7e8ac6736e8a5
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/gnome/sources/meld/1.8/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/meld
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	meld.license
COMPONENT_CLASSIFICATION=	Development/Editors

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

PKG_OPTIONS +=		-D COMPONENT_DESCRIPTION="$(COMPONENT_DESCRIPTION)"
PKG_MACROS +=		PYVER=$(PYTHON_VERSION)

COMPONENT_BUILD_ENV += PYTHON=$(PYTHON)

# Meld has no configure however it honors DESTDIR which is necessary so
# we don't try to install into roots /usr but rather our proto areas usr
COMPONENT_INSTALL_ARGS +=	DESTDIR=$(PROTO_DIR)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += text/rarian

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/pygtk2-27
REQUIRED_PACKAGES += runtime/python-27
