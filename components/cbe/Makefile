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
# Copyright 2011, Andrzej Szeszo
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		cbe
COMPONENT_VERSION=	1.8.0

include ../../make-rules/ips.mk

#PKGMANGLE = true
PKGLINT = true

download:

prep:

configure:

build:

install:
	rm -rf $(PROTO_DIR)
	mkdir -p $(PROTO_DIR)/opt/dtbld/bin
	mkdir -p $(PROTO_DIR)/opt/dtbld/lib/cbe-env
	cp files/bin/* $(PROTO_DIR)/opt/dtbld/bin
	cp files/cbe-env/* $(PROTO_DIR)/opt/dtbld/lib/cbe-env

test:		$(NO_TESTS)

clean:
	rm -rf $(BUILD_DIR)

clobber: clean
