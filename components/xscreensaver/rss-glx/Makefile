#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2013 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rss-glx
COMPONENT_VERSION= 	0.91
HUMAN_VERSION=		0.9.1
COMPONENT_PROJECT_URL=	http://sourceforge.net/projects/rss-glx/


COMPONENT_SRC=		$(COMPONENT_NAME)_$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:8f8d773864695fd57e6ff21f430994369ad74c69a5e66ce510bbba8ca55333aa
COMPONENT_ARCHIVE_URL=	http://downloads.sourceforge.net/project/rss-glx/rss-glx/$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Note: currently only 32-bit build is of interest, but with a location
# under /usr/lib, the CONFIGURE_PREFIX should consider bitness in this recipe
XSCREENSAVER_PREFIX.32 = $(USRLIBDIR)/xscreensaver
XSCREENSAVER_PREFIX.64 = $(USRLIBDIR64)/xscreensaver
XSCREENSAVER_PREFIX    = $(XSCREENSAVER_PREFIX.$(BITS))
XSCREENSAVER_HACKDIR.$(BITS)   = $(XSCREENSAVER_PREFIX.$(BITS))/hacks
XSCREENSAVER_CONFDIR   = $(XSCREENSAVER_PREFIX.32)/config

CONFIGURE_PREFIX    = $(XSCREENSAVER_PREFIX)
CONFIGURE_MANDIR    = $(USRSHAREMANDIR)
CONFIGURE_BINDIR.$(BITS) = $(XSCREENSAVER_HACKDIR.$(BITS))

COMPONENT_PRE_CONFIGURE_ACTION += chmod -R u+r $(SOURCE_DIR)/ && \
			cp -r $(SOURCE_DIR)/* $(@D)

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

CONFIGURE_ENV+=	"XGETTEXT=/usr/gnu/bin/xgettext"
CONFIGURE_ENV+= "GNOME_DATADIR=$(XSCREENSAVER_CONFDIR)"
CONFIGURE_ENV+= "GLADE_DATADIR=$(XSCREENSAVER_CONFDIR)"

CPPFLAGS+=		-D_FILE_OFFSET_BITS=64

CONFIGURE_OPTIONS+=	--disable-sound
CONFIGURE_OPTIONS+=	--with-configdir=$(XSCREENSAVER_CONFDIR)/control-center-2.0
CONFIGURE_OPTIONS+= 	CPPFLAGS="$(CXXFLAGS)"

#COMPONENT_INSTALL_ENV += MAKEFLAGS=-e install_prefix=$(PROTO_DIR)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk


