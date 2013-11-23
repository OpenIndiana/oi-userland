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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	numpy
COMPONENT_VERSION= 	1.4.1
COMPONENT_SUMMARY= 	Python XML module
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:2e7bb84573e5123e07f3c919fd433bc09b78d606252b6b719e385c2a981d8e06
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/$(COMPONENT_NAME)/files/NumPy/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://numpy.scipy.org/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

LD_OPTIONS	+= -lm

COMPONENT_PRE_BUILD_ACTION  +=	$(CLONEY) $(SOURCE_DIR) $(@D) ;

# This ugly hack is necessary to compile 64-bit modules
# http://mail.scipy.org/pipermail/numpy-discussion/2010-June/051189.html
COMPONENT_PRE_BUILD_ACTION  +=	echo '\#!/bin/sh' > $(BUILD_DIR)/fake_cc ;
COMPONENT_PRE_BUILD_ACTION  +=	echo 'gcc -m$(BITS) $$@' >> $(BUILD_DIR)/fake_cc ;
COMPONENT_PRE_BUILD_ACTION  +=	chmod 755 $(BUILD_DIR)/fake_cc

COMPONENT_PRE_INSTALL_ACTION  +=	echo '\#!/bin/sh' > $(BUILD_DIR)/fake_cc ;
COMPONENT_PRE_INSTALL_ACTION  +=	echo 'gcc -m$(BITS) $$@' >> $(BUILD_DIR)/fake_cc ;
COMPONENT_PRE_INSTALL_ACTION  +=	chmod 755 $(BUILD_DIR)/fake_cc
	
COMPONENT_POST_BUILD_ACTION =	$(RM) $(BUILD_DIR)/fake_cc
COMPONENT_POST_INSTALL_ACTION =	$(RM) $(BUILD_DIR)/fake_cc

CC=$(BUILD_DIR)/fake_cc

COMPONENT_BUILD_ARGS	=	--fcompiler=gnu95 
COMPONENT_POST_INSTALL_ACTION = ( $(GSED) -i -e 's:\#!/usr/bin/env python2\.6:\#!/usr/bin/python2.6:' \
	$(PROTO_DIR)/usr/bin/f2py2.6 && \
	$(GSED) -i -e 's:\#!/usr/bin/env python:\#!/usr/bin/python2.6:' \
	$(PROTO_DIR)/usr/lib/python2.6/vendor-packages/numpy/f2py/diagnose.py )

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
