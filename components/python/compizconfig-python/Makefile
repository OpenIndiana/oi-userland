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

COMPONENT_NAME=		compizconfig-python
COMPONENT_VERSION=	0.8.4
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.compiz.org
COMPONENT_SUMMARY=	compizconfig libraries - is an alternative configuration system for compiz
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:6734ae35ee69d081f35f98a89cd3bccb411a4db7c5b35fbd226270d95ac76f5a
COMPONENT_ARCHIVE_URL=	http://releases.compiz.org/components/compizconfig-python/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION = \
	( cd $(@D) ; \
		libtoolize --force --copy &&\
		aclocal -I .  &&\
		autoheader &&\
		autoconf )


CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_ENV+=		PYTHON=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
