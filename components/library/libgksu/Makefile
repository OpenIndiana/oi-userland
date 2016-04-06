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

COMPONENT_NAME=		libgksu
COMPONENT_VERSION=	2.0.12
COMPONENT_REVISION=	4
COMPONENT_PROJECT_URL=	http://www.nongnu.org/gksu/
COMPONENT_SUMMARY=	Simple API for embedded_su, pfexec and sudo (optional)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:22f9cfc3627dcb6774b9aff66c6ea6554f3b34b82bbfa2467b821e67874c3faf
COMPONENT_ARCHIVE_URL=	http://people.debian.org/~kov/gksu/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					$(TOUCH) NEWS  README&&\
					libtoolize --copy --force &&\
					aclocal &&\
					automake -a -c -f && \
                                        autoconf &&\
					intltoolize --force  --copy )

CONFIGURE_OPTIONS+=	--disable-scrollkeeper

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
