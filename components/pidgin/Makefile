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

COMPONENT_NAME=		pidgin
COMPONENT_VERSION=	2.10.8
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.pidgin.im
COMPONENT_SUMMARY=	Multiprotocol Instant Messaging Client
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:b633367e3588ff3e615d68e812302dfdbe32e73693cbe42a0d827b7aed7a8227
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/Pidgin/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
			                libtoolize --force && \
					intltoolize --force --copy --automake && \
					aclocal -I. && \
					automake -a -f -c &&\
					autoconf )

COMPONENT_PRE_CONFIGURE_ACTION = ( cp -rp $(SOURCE_DIR)/* $(@D) && \
                                        cp -rp $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE))

CONFIGURE_SCRIPT=       $(@D)/configure

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--enable-gnutls=no
CONFIGURE_OPTIONS+=	--with-nss-includes=/usr/include/mps
CONFIGURE_OPTIONS+=	--with-nss-libs=/usr/lib/mps
CONFIGURE_OPTIONS+=	--with-nspr-includes=/usr/include/mps
CONFIGURE_OPTIONS+=	--with-nspr-libs=/usr/lib/mps
CONFIGURE_OPTIONS+=	--enable-gnome-keyring
CONFIGURE_OPTIONS+=	--disable-gevolution
CONFIGURE_OPTIONS+=	--enable-cap
CONFIGURE_OPTIONS+=	--disable-meanwhile
CONFIGURE_OPTIONS+=	--disable-nm
CONFIGURE_OPTIONS+=	--disable-consoleui
CONFIGURE_OPTIONS+=	--disable-vv
CONFIGURE_OPTIONS+=	--enable-perl=yes

CONFIGURE_ENV+=	INTLTOOL_PERL=$(PERL)
CONFIGURE_ENV+=	PERL=$(PERL)
CONFIGURE_ENV+=	perlpath=$(PERL)
CONFIGURE_ENV+=	PYTHON=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
