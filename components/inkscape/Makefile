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
# Copyright 2015 Aurelien Larcher
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		inkscape
COMPONENT_VERSION=	0.48.5
COMPONENT_FMRI=		image/editor/inkscape
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_SUMMARY=	Opensource professional vector graphics editor
COMPONENT_PROJECT_URL=	http://www.inkscape.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:2b6ce684f9f2a0691ab454656424555cbda131db78e13973360684bc833ad969
COMPONENT_ARCHIVE_URL=	http://inkscape.global.ssl.fastly.net/media/sourceforge/files/0.48.5/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE = GPLv2
COMPONENT_LICENSE_FILE = $(COMPONENT_NAME).license


include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =	( cd $(@D)  && \
				libtoolize --force &&\
				intltoolize --force --copy --automake &&\
				aclocal -I. &&\
				automake -a -c -f &&\
				autoconf)

CONFIGURE_OPTIONS+=  --enable-lcms
CONFIGURE_OPTIONS+=  --enable-poppler-cairo
CONFIGURE_OPTIONS+=  --disable-binreloc
CONFIGURE_OPTIONS+=  --with-gnome-vfs


# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
