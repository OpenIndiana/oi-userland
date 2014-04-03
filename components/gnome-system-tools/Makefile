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

COMPONENT_NAME=		gnome-system-tools
COMPONENT_VERSION=	2.14.0
IPS_COMPONENT_VERSION=	2.30.0
COMPONENT_PROJECT_URL=	https://projects.gnome.org/gst/
COMPONENT_SUMMARY=	GNOME System Tools
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:39f37363001b1cc2f5d2f5d2d7024a7a36e7dd227862b1dd9ce8c3325157ea7c
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.14/$(COMPONENT_ARCHIVE)

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

COMPONENT_PRE_CONFIGURE_ACTION =        (chmod -R u+r $(SOURCE_DIR) && cp -rp $(SOURCE_DIR)/* $(@D) && \
                                        cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE) all )

CONFIGURE_SCRIPT=       $(@D)/configure

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-scrollkeeper

CONFIGURE_ENV += GKSU_CFLAGS="`pkg-config libgksu2 --cflags`"
CONFIGURE_ENV += GKSU_LIBS="`pkg-config libgksu2 --libs`"
CONFIGURE_ENV += LIBS="-lm"

CFLAGS += -D NOPTY -D USE_AUTHEN_PAM
CFLAGS += -I/usr/include/gnome-vfs-2.0 -I/usr/lib/gnome-vfs-2.0/include
LDFLAGS += -lgnomevfs-2

COMPONENT_INSTALL_ENV += GCONF_DISABLE_MAKEFILE_SCHEMA_INSTALL=1

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
