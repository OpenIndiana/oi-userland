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
# Copyright (c) 2013 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rss-glx
# Don't change - compatibility issues
COMPONENT_VERSION= 	0.91
HUMAN_VERSION=		0.9.1
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/rss-glx/


COMPONENT_SRC=		$(COMPONENT_NAME)_$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:8f8d773864695fd57e6ff21f430994369ad74c69a5e66ce510bbba8ca55333aa
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/rss-glx/rss-glx/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION += chmod -R u+r $(SOURCE_DIR)/ && \
			cp -r $(SOURCE_DIR)/* $(@D) 

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

CONFIGURE_ENV+=	"XGETTEXT=/usr/gnu/bin/xgettext"
CONFIGURE_ENV+= "GNOME_DATADIR=/usr/lib/xscreensaver/config"
CONFIGURE_ENV+= "GLADE_DATADIR=/usr/lib/xscreensaver/config"


CPPFLAGS+=		-D_FILE_OFFSET_BITS=64

CONFIGURE_OPTIONS+=	--disable-sound
CONFIGURE_OPTIONS+=	--prefix=/usr/lib/xscreensaver
CONFIGURE_OPTIONS+=	--bindir=/usr/lib/xscreensaver/hacks
CONFIGURE_OPTIONS+=	--mandir=/usr/share/man
CONFIGURE_OPTIONS+=	--with-configdir=/usr/lib/xscreensaver/config/control-center-2.0
CONFIGURE_OPTIONS+= 	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS+= 	CPPFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS+= 	LDFLAGS="$(LDFLAGS)"
CONFIGURE_OPTIONS+= 	CC="$(CC)"
CONFIGURE_OPTIONS+= 	CXX="$(CXX)"

#COMPONENT_INSTALL_ENV += MAKEFLAGS=-e install_prefix=$(PROTO_DIR)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../../make-rules/depend.mk


