#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= sysbench

COMPONENT_VERSION= 0.4.12
COMPONENT_SUMMARY= Sysbench - sytem performance benchmark
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:83fa7464193e012c91254e595a89894d8e35b4a38324b52a5974777e3823ea9e
COMPONENT_ARCHIVE_URL=  \
	http://downloads.sourceforge.net/project/$(COMPONENT_NAME)/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://sysbench.sourceforge.net/

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PREP_ACTION+=        (cd $(@D) && libtoolize -c && $(ACLOCAL))

COMPONENT_POST_INSTALL_ACTION+= \
        $(CP) $(COMPONENT_SRC)/doc/manual.xml $(PROTOUSRSHAREDOCDIR)/$(COMPONENT_NAME)

CONFIGURE_OPTIONS +=    --with-mysql=/usr/mariadb/5.5
CONFIGURE_OPTIONS +=    --enable-largefile
CONFIGURE_OPTIONS +=    --bindir=/usr/benchmarks/sysbench/bin

install: $(INSTALL_32) 

build: $(BUILD_32)

install: $(INSTALL_32)
