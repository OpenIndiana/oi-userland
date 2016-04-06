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
# Copyright (c) 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gimp
COMPONENT_VERSION=	2.8.14
COMPONENT_PROJECT_URL=	http://www.gimp.org/
COMPONENT_SUMMARY=	The Gimp image editor
COMPONENT_FMRI=		image/editor/gimp
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:d82a958641c9c752d68e35f65840925c08e314cea90222ad845892a40e05b22d
COMPONENT_ARCHIVE_URL=	http://download.gimp.org/pub/gimp/v2.8/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS += -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include

COMPONENT_PREP_ACTION =	( cd $(@D)  && \
				libtoolize --force &&\
				intltoolize --force --copy --automake &&\
				aclocal -I. &&\
				automake -a -c -f &&\
				autoconf)

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS+=	--localstatedir=/var/lib
CONFIGURE_OPTIONS+=	--enable-mp
CONFIGURE_OPTIONS+=	--enable-default-binary
CONFIGURE_OPTIONS+=	--enable-mmx=no
CONFIGURE_OPTIONS+=	--with-lcms=2
#CONFIGURE_OPTIONS+=	--enable-glibtest=no

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
