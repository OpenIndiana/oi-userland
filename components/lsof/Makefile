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
# Copyright 2016 Jim Klimov. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		lsof
COMPONENT_VERSION=	4.89
COMPONENT_PROJECT_URL=	http://freecode.com/projects/util-linux
COMPONENT_SUMMARY=	LSOF - lister of opened files
COMPONENT_SRC=		$(COMPONENT_NAME)_$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
# Theoretical upstream is ftp://lsof.itap.purdue.edu/pub/tools/unix/lsof
# but it is not available at the time of this writing
COMPONENT_ARCHIVE_URL=	ftp://sunsite.ualberta.ca/pub/Mirror/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	\
    sha256:81ac2fc5fdc944793baf41a14002b6deb5a29096b387744e28f8c30a360a3718

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PREP_ACTION = \
    ( cd $(SOURCE_DIR) && tar xf - < $(COMPONENT_SRC)_src.tar && \
      { echo '\#!/bin/sh'; echo 'true'; } > ./configure && chmod +x configure )

COMPONENT_PRE_BUILD_ACTION = \
    ( cd $(@D) && cp -prf "$(SOURCE_DIR)/$(COMPONENT_SRC)_src"/./ ./ && \
      yes '' | SOLARIS_KERNBITS=$(BITS) ./Configure solaris )

build:		$(BUILD_32_and_64)

# The p5m manifest directly pulls from source dirs
install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

include ../../make-rules/depend.mk
