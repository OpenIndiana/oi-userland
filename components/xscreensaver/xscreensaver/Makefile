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

COMPONENT_NAME=		xscreensaver
# Don't change - compatibility issues
COMPONENT_VERSION=	5.11
HUMAN_VERSION= 		5.15
COMPONENT_PROJECT_URL=	http://www.jwz.org/xscreensaver/


COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:4f6d1f1e4c15dbb74e2296f8fe57a73d47d602515178c248bbc838f779d5082d
COMPONENT_ARCHIVE_URL=	ftp://ftp.FreeBSD.org/pub/FreeBSD/ports/distfiles/$(COMPONENT_ARCHIVE)

PATCH_LEVEL=		0

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

COMPONENT_POST_UNPACK_ACTION=	( cp -r $(COMPONENT_DIR)/files/po-sun/* $(SOURCE_DIR)/po && \
					cp $(COMPONENT_DIR)/files/*.p5i.in $(SOURCE_DIR)/driver && \
					chmod a+x  $(SOURCE_DIR)/install-sh && \
					mkdir -p $(SOURCE_DIR)/mesa/GL && \
					ln -s /usr/include/mesa/*.h $(SOURCE_DIR)/mesa/GL )

COMPONENT_PRE_CONFIGURE_ACTION += chmod -R u+r $(SOURCE_DIR)/ && \
			cp -r $(SOURCE_DIR)/* $(@D) && \
                        cd $(@D) && autoconf

PATH=/usr/gnu/bin:/usr/bin:/usr/perl5/bin

CONFIGURE_SCRIPT=	$(@D)/configure

CFLAGS+=	-funsafe-math-optimizations -Wall -I$(SOURCE_DIR)/mesa/GL  -std=gnu99
CXXFLAGS+=	-funsafe-math-optimizations -Wall -I$(SOURCE_DIR)/mesa/GL
LDFLAGS+=	-I$(@D)/mesa/GL 
LDFLAGS+=	$(CC_BITS)

CONFIGURE_ENV+=	"XGETTEXT=/usr/gnu/bin/xgettext"
CONFIGURE_ENV+= "GNOME_DATADIR=/usr/lib/xscreensaver/config"
CONFIGURE_ENV+= "GLADE_DATADIR=/usr/lib/xscreensaver/config"


CONFIGURE_OPTIONS+=	--enable-maintainer-mode 
CONFIGURE_OPTIONS+=	--with-gnome 
CONFIGURE_OPTIONS+=	--enable-gtk-doc
CONFIGURE_OPTIONS+=	--with-gtk2=/usr
CONFIGURE_OPTIONS+=	--with-pixbuf=/usr 
CONFIGURE_OPTIONS+=	--enable-locking
CONFIGURE_OPTIONS+=	--with-pam=/usr 
CONFIGURE_OPTIONS+=	--without-shadow
CONFIGURE_OPTIONS+=	--without-kerberos 
CONFIGURE_OPTIONS+=	--with-dpms
CONFIGURE_OPTIONS+=	--with-xinput-ext
CONFIGURE_OPTIONS+=	--with-randr-ext
CONFIGURE_OPTIONS+=	--enable-root-passwd
CONFIGURE_OPTIONS+=	--with-gl=/usr
CONFIGURE_OPTIONS+=	--without-motif
CONFIGURE_OPTIONS+=	--with-jpeg=/usr
CONFIGURE_OPTIONS+=	--with-hackdir=/usr/lib/xscreensaver/hacks 
CONFIGURE_OPTIONS+=	 --libexecdir=/usr/lib/xscreensaver/bin
CONFIGURE_OPTIONS+=	--with-configdir=/usr/lib/xscreensaver/config/control-center-2.0
CONFIGURE_OPTIONS+=	--with-image-directory=/usr/share/pixmaps/backgrounds
CONFIGURE_OPTIONS+=	--with-text-file=/etc/motd
CONFIGURE_OPTIONS+=	--with-x-app-defaults=/usr/share/X11/app-defaults
CONFIGURE_OPTIONS+= 	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS+= 	CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS+= 	LDFLAGS="$(LDFLAGS)"

COMPONENT_POST_CONFIGURE_ACTION+=	( \
	cd $(@D)/po && \
	make generate_potfiles_in -o Makefile && \
	make POTFILES -o Makefile && \
	make generate_potfiles_in POTFILES xscreensaver.pot -o Makefile &&  \
	touch stamp-it )

COMPONENT_INSTALL_ENV += MAKEFLAGS=-e install_prefix=$(PROTO_DIR)

../rss-glx/build/i86/.built:
	(cd ../rss-glx ; $(GMAKE) build)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32) ../rss-glx/build/i86/.built
	perl ../rss-glx/build/i86/utils/rss-glx_install.pl $(PROTO_DIR)/usr/share/X11/app-defaults/XScreenSaver
test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../../make-rules/depend.mk


