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
# Copyright 2016 Alexander Pyhalov
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-user-docs
COMPONENT_VERSION=	2.32.0
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	GNOME user documentation
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:d42c4435590e5b79c8fcf1d917aee485096c02cdc84338bc31f769219ccc87f7
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.32/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		documentation/gnome/gnome-user-docs
COMPONENT_CLASSIFICATION=Desktop (GNOME)/Documentation
COMPONENT_LICENSE=	FDL1.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && for f in gnome2-user-guide/bg/*.xml gnome2-user-guide/zh_CN/*.xml; do \
					dos2unix -ascii $$f $$f ; done) 

CONFIGURE_OPTIONS+=	--disable-scrollkeeper

CONFIGURE_ENV+= PYTHON=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += developer/gnome/gnome-doc-utils
REQUIRED_PACKAGES += system/extended-system-utilities
