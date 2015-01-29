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

COMPONENT_NAME=		dasher
COMPONENT_VERSION=	4.11
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Predictive text entry system
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:fb21cc4ef606e10a8e5deffebe8695a376eabb0766d7d1bdf80abc5f03f4fed2
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		gnome/accessibility/dasher
COMPONENT_CLASSIFICATION=	Applications/Universal Access
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					glib-gettextize --force &&\
					libtoolize --force &&\
					intltoolize --force --copy &&\
					aclocal -I m4 &&\
					autoconf &&\
					autoheader &&\
					automake -c -f -a)

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -rp $(SOURCE_DIR)/* $(@D) && \
                                        cp -r $(COMPONENT_DIR)/files/po-sun $(@D) && \
                                        cd $(@D)/po-sun && $(MAKE) all )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

CONFIGURE_ENV+= PYTHON="$(PYTHON)"
CONFIGURE_ENV+= PERL="$(PERL)"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
