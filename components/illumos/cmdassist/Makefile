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

COMPONENT_NAME=		cmdassist
COMPONENT_VERSION=	0.5.11
COMPONENT_PROJECT_URL=	http://www.openindiana.org
COMPONENT_SUMMARY=	Command Assistant
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:41807d82f2ca7a983095ff32b709ae57d5b57f3c0a4b4f2e3b3349ece0a5eacd
COMPONENT_ARCHIVE_URL=	http://dlc.openindiana.org/oi-build/source-archives/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	cmdassist.license
COMPONENT_LICENSE=	CDDL
COMPONENT_FMRI=		gnome/cmdassist
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Documentation

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					libtoolize --copy --force &&\
					glib-gettextize -f &&\
					intltoolize --force --copy &&\
					gnome-doc-prepare --force &&\
					gnome-doc-common &&\
					aclocal  &&\
					autoheader &&\
					automake -c -f -a &&\
					autoconf )

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)
