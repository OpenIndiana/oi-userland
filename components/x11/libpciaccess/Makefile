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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=	libpciaccess
COMPONENT_VERSION=	0.13.5
COMPONENT_PROJECT_URL=	http://xorg.freedesktop.org
COMPONENT_SUMMARY=	scanpci and libpciaccess - generic PCI access software
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:752c54e9b3c311b4347cb50aea8566fa48eab274346ea8a06f7f15de3240b999
COMPONENT_ARCHIVE_URL=	http://xorg.freedesktop.org/releases/individual/lib/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	System/Hardware
COMPONENT_FMRI=		diagnostic/scanpci
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Missing files in build dir for configure without this.
COMPONENT_PREP_ACTION =        (cd $(@D) && \
                                        libtoolize --automake --copy --force && \
                                        aclocal -Im4 && \
                                        autoheader && \
                                        automake -a -f -c &&\
                                        autoconf )

PATH=/usr/gnu/bin:/usr/bin

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += developer/build/autoconf/xorg-macros

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
