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

COMPONENT_NAME=		stardict
COMPONENT_VERSION=	3.0.3
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.stardict.org/
COMPONENT_SUMMARY=	A powerful dictionary platform written in GTK+2
COMPONENT_FMRI=		system/desktop/stardict
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:9ba10a5b3dcdd02b81c7a138dac15903a6bc2355856f60338f3775e371472b73
COMPONENT_ARCHIVE_URL=	ftp://tux.rainside.sk/gentoo/distfiles/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/mariadb/5.5/bin:/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
                                        autoreconf  -f -i )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--enable-deprecations
CONFIGURE_OPTIONS+=	--disable-festival
CONFIGURE_OPTIONS+=	--disable-advertisement
CONFIGURE_OPTIONS+=	--disable-gucharmap

CPPFLAGS += -I/usr/mariadb/5.5/include
LDFLAGS.32 += -L/usr/mariadb/5.5/lib -R/usr/mariadb/5.5/lib
LDFLAGS += $(LDFLAGS.$(BITS))

LDFLAGS += -lnsl -lsocket

CONFIGURE_ENV += CPPFLAGS=$(CPPFLAGS)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
