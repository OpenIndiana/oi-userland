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

COMPONENT_NAME=		libcompizconfig
COMPONENT_VERSION=	0.8.8
COMPONENT_PROJECT_URL=	http://www.compiz.org/
COMPONENT_SUMMARY=	compizconfig libraries - is an alternative configuration system for compiz
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:50a81aba31d9517587f7d046b7161eb4204ddceb422d09d036a412bb80381490
COMPONENT_ARCHIVE_URL=	http://releases.compiz.org/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D) && \
					rm -f ltmain.sh &&\
			                libtoolize --automake --copy --force && \
					aclocal -I. && \
				        autoheader && \
					automake -a -f -c &&\
					autoconf )

#LDFLAGS += -L/usr/X11/lib -L/usr/openwin/lib -R/usr/X11/lib -R/usr/openwin/lib -lX11 -lXext

CONFIGURE_OPTIONS+=	--sysconfdir=/etc

CONFIGURE_PREFIX= /usr/g++

CONFIGURE_ENV+= INTLTOOL_PERL=$(PERL)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
