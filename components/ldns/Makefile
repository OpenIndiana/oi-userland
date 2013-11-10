#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

# Copyright (c) 2013, Adam Stevko <adam.stevko@gmail.com> 

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		ldns
COMPONENT_VERSION=	1.6.16
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:24b2f9cb05797170f2021ef0e0372d4b5225ee4199f0568a15589b5c524df695
COMPONENT_PROJECT_URL=	http://www.nlnetlabs.nl/projects/ldns/	
COMPONENT_ARCHIVE_URL=	http://www.nlnetlabs.nl/downloads/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)	

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS +=    --with-examples
CONFIGURE_OPTIONS +=    --with-drill
CONFIGURE_OPTIONS +=	--disable-static	
CONFIGURE_OPTIONS +=	--disable-gost	
CONFIGURE_OPTIONS +=	--disable-ecdsa

build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TESTS_32)
