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
# Copyright (c) 2018 Michal Nowak
#

PREFERRED_BITS=	64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		compiz-bcop
COMPONENT_VERSION=	0.8.14
COMPONENT_FMRI=		desktop/compiz/bcop
COMPONENT_CLASSIFICATION=Development/Other Languages
COMPONENT_PROJECT_URL=	http://www.northfield.ws/
COMPONENT_SUMMARY=	beryl compiz XML option parser
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5e495317ba6f17eaba8c7316e2a0c9a9b0b8d5b692dd7548ab0d90ba18891174
COMPONENT_ARCHIVE_URL=	http://www.northfield.ws/projects/compiz/releases/$(COMPONENT_VERSION)/$(COMPONENT_SRC).tar.xz
COMPONENT_LICENSE=	MIT, LGPLv2.1, GPLv2


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
	aclocal -I. && \
        autoheader && \
        libtoolize --automake --copy --force && \
	automake -a -f -c &&\
	autoconf )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--with-getopt=/usr/gnu/bin/getopt

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += shell/bash
