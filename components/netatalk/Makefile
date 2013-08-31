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
# Copyright 2013, Jon Tibble.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=         netatalk
COMPONENT_VERSION=      3.0.5
COMPONENT_PROJECT_URL=	http://netatalk.sourceforge.net/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:884247728b56b510347785f576be2df76afb293649870c4cd7fdb3048a64b4a9
COMPONENT_ARCHIVE_URL=  http://downloads.sourceforge.net/netatalk/netatalk-3.0.5.tar.bz2

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPILER =	gcc

CONFIGURE_OPTIONS +=	--with-init-style=solaris
CONFIGURE_OPTIONS +=	--enable-krbV-uam

COMPONENT_POST_INSTALL_ACTION_32 =	$(GSED) -i -e 's!usr/bin/env python!usr/bin/python2.6!' $(PROTO_DIR)$(USRBINDIR)/afpstats
COMPONENT_POST_INSTALL_ACTION_64 =	$(GSED) -i -e 's!usr/bin/env python!usr/bin/amd64/python2.6!' $(PROTO_DIR)$(USRBINDIR64)/afpstats
COMPONENT_POST_INSTALL_ACTION =		( $(COMPONENT_POST_INSTALL_ACTION_$(BITS)) )

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

