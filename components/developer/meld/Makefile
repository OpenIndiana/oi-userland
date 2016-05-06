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
COMPONENT_VERSION=	3.16.0
COMPONENT_FMRI=		developer/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	meld - graphical diff and merge tool
COMPONENT_DESCRIPTION=\
Meld is a visual diff and merge tool. You can compare two or three files \
and edit them in place (diffs update dynamically). You can compare two or \
three folders and launch file comparisons. You can browse and view a working \
copy from popular version control systems such such as Git, CVS, Subversion, \
Bazaar-ng and Mercurial.
COMPONENT_PROJECT_URL=	http://meldmerge.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:341bfd53ac7c0167d6d43694c0e7dbedf76463bdf79b425c439376ba15b56c0a
COMPONENT_ARCHIVE_URL=	https://download.gnome.org/sources/meld/3.16/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/meld
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	Development/Editors

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# The python-2.7 is in Meld-3.x requirements
# Note the build also reqires an "xml-parser-XYZ" package installed,
# for the current XYZ == version of Perl ($PERL_VERSION)
PYTHON_VERSION=	2.7
PYTHON_VERSIONS=	$(PYTHON_VERSION)
PKG_MACROS +=	PYTHON_VERSION="$(PYTHON_VERSION)"
PKG_MACROS +=	PYTHON_LIB="$(PYTHON_LIB)"
PKG_MACROS +=	PYVER=$(PYTHON_VERSION)

# Install resource files under here (share/meld etc. added by setup.py):
PYTHON_DATA =	$(USRDIR)

# Meld py/pyc files are implementation detail, not generally useful Python libs
PYTHON_LIB =	$(USRLIBDIR)/$(COMPONENT_NAME)

PKG_OPTIONS +=	-D COMPONENT_DESCRIPTION="$(COMPONENT_DESCRIPTION)"
PKG_OPTIONS +=	-D PYTHON_VERSION="$(PYTHON_VERSION)"


# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
