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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		socat
COMPONENT_VERSION=	1.7.3.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:ce3efc17e3e544876ebce7cd6c85b3c279fda057b2857fcaaf67b9ab8bdaf034
COMPONENT_PROJECT_URL=	http://www.dest-unreach.org/socat/
COMPONENT_ARCHIVE_URL=	http://www.dest-unreach.org/socat/download/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

build:          $(BUILD_32)

install:        $(INSTALL_32)

REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += system/library
