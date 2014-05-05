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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		compiz
COMPONENT_VERSION=	0.8.8
COMPONENT_PROJECT_URL=	http://www.compiz.org/
COMPONENT_SUMMARY=	OpenGL compositing window manager
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:1c2af8553ea16379393630d16f3ccdd4487c41d099e4f54358e71543df13ac00
COMPONENT_ARCHIVE_URL=	http://releases.compiz.org/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
					aclocal -I. && \
				        autoheader && \
			                libtoolize --automake --copy --force && \
					automake -a -f -c &&\
					autoconf )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--enable-gnome
CONFIGURE_OPTIONS+=	--without-xcb
CONFIGURE_OPTIONS+=	--with-default-plugins=core,dbus,move,place,png,regex,resize,svg,switcher,imgjpeg,resizeinfo,session,text,workarounds,decoration,animation,wall,fade,gnomecompat

CONFIGURE_ENV+=	INTLTOOL_PERL=$(PERL)
CONFIGURE_ENV+=	PYTHON=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
