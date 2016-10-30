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
# Copyright 2011, Andrzej Szeszo
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		javahelp
COMPONENT_VERSION=	2_0_05
COMPONENT_SRC=		jh2.0
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH=	sha256:285728ab8cbebd2b51531fb7c7fb3213e6cf82bd8d1851ccd0ca78af7a11189f
COMPONENT_ARCHIVE_URL=	ftp://ftp.internat.freebsd.org/pub/FreeBSD/distfiles/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk

build: prep

install: build
	[ -d $(PROTO_DIR) ] || mkdir -p $(PROTO_DIR)

clean::
	rm -rf $(BUILD_DIR)
