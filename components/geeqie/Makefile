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

COMPONENT_NAME=		geeqie
COMPONENT_VERSION=	1.1
COMPONENT_PROJECT_URL=	http://geeqie.sourceforge.net/
COMPONENT_SUMMARY=	Geeqie is a lightweight Gtk+ based image viewer
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5544e81c29917a647f19bfe800d9f0dd1cd5b890329feebd9abd80927e1afecf
COMPONENT_ARCHIVE_URL=	 http://prdownloads.sourceforge.net/geeqie/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	Applications/Graphics and Imaging
COMPONENT_LICENSE=      GPLv2
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_FMRI=         image/viewer/geeqie

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && aclocal  -I . && \
					libtoolize --force --copy&&\
					autoheader &&\
					automake -a -f -c --gnu &&\
					autoconf )

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_ENV += LIBS="-lm -lsocket -lnsl"

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
