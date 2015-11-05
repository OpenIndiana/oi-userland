#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Ivan Richwalski <ivan@seppuku.net>
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		multitail
COMPONENT_FMRI=		text/$(COMPONENT_NAME)
COMPONENT_VERSION=	6.4.2
COMPONENT_REVISION=	0
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	license.txt
COMPONENT_PROJECT_URL=	https://www.vanheusden.com/$(COMPONENT_NAME)/
COMPONENT_SUMMARY=	multitail - monitor multiple logfiles and command output in a terminal
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:af1d5458a78ad3b747c5eeb135b19bdca281ce414cefdc6ea0cff6d913caa1fd
COMPONENT_ARCHIVE_URL=	https://www.vanheusden.com/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

COMPONENT_BUILD_ENV += CFLAGS="-I/usr/include/ncurses"
COMPONENT_BUILD_ENV += EXTRA_LDFLAGS="-L/usr/gnu/lib -R/usr/gnu/lib"
COMPONENT_BUILD_ARGS += -f makefile.solaris_gcc

#CONFIGURE_OPTIONS +=	LIBS="-lncurses"

build:		$(BUILD_32)

install:	$(INSTALL_32)

include ../../make-rules/depend.mk
