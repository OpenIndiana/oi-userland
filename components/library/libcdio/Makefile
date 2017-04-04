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
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libcdio
COMPONENT_VERSION=	0.94
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/libcdio/
COMPONENT_SUMMARY=	GNU Compact Disc Input and Control Library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:96e2c903f866ae96f9f5b9048fa32db0921464a2286f5b586c0f02699710025a
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/libcdio/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_FMRI= 	library/audio/libcdio

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CPPFLAGS += -I/usr/include/dbus-1.0 -I/usr/lib/dbus-1.0/include -DDBUS_API_SUBJECT_TO_CHANGE
CPPFLAGS += -D_FILE_OFFSET_BITS=64

LDFLAGS += -lhal -ldbus-1

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-cpp-progs
CONFIGURE_OPTIONS+=	--disable-cxx
CONFIGURE_OPTIONS+=	--disable-static

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"
CONFIGURE_ENV += am_cv_lib_iconv=no

COMPONENT_POST_INSTALL_ACTION= \
	(cd $(PROTOUSRDIR) ;  $(MV) include/cdio/cdio_config.h include/cdio/cdio_config-$(BITS).h )

ENV = /usr/bin/env -i

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/audio/libcddb
REQUIRED_PACKAGES += service/hal
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus
