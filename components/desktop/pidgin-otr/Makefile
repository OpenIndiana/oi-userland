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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pidgin-otr
COMPONENT_VERSION=	4.0.2
COMPONENT_PROJECT_URL=	http://www.cypherpunks.ca/otr/
COMPONENT_SUMMARY=	Off-the-Record (OTR) Messaging plugin for Pidgin
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f4b59eef4a94b1d29dbe0c106dd00cdc630e47f18619fc754e5afbf5724ebac4
COMPONENT_ARCHIVE_URL=	http://www.cypherpunks.ca/otr/$(COMPONENT_ARCHIVE)

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

CONFIGURE_ENV+=	PERL=$(PERL)
CONFIGURE_ENV+=	INTLTOOL_PERL=$(PERL)
CONFIGURE_ENV+=	PYTHON=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += communication/im/pidgin

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libotr
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
