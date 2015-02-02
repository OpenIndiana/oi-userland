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
# Copyright (c) 2012, Adam Stevko <adam.stevko@gmail.com> 
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		socat
COMPONENT_VERSION=	1.7.3.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:f8de4a2aaadb406a2e475d18cf3b9f29e322d4e5803d8106716a01fd4e64b186
COMPONENT_PROJECT_URL=	http://www.dest-unreach.org/socat/
COMPONENT_ARCHIVE_URL=	http://www.dest-unreach.org/socat/download/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

build:          $(BUILD_32)

install:        $(INSTALL_32)
