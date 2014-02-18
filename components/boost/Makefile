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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= boost
COMPONENT_VERSION= 1.55.0
COMPONENT_SUMMARY= boost - free peer-reviewed portable C++ source libraries
COMPONENT_SRC= $(COMPONENT_NAME)_1_55_0
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:fff00023dd79486d444c8e29922f4072e1d451fc5a4d2b6075852ead7f2b7b52
COMPONENT_ARCHIVE_URL= \
  http://sourceforge.net/projects/boost/files/boost/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_PROJECT_URL = http://www.boost.org

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk

PKG_PROTO_DIRS += $(SOURCE_DIR)/doc/html

CLEAN_PATHS += $(BUILD_DIR)

LDFLAGS.32=-L/usr/g++/lib -R/usr/g++/lib
LDFLAGS+=$(LDFLAGS.$(BITS))

$(BUILD_32):    $(SOURCE_DIR)/.prep
	$(MKDIR) $(@D) 
	cp -a $(SOURCE_DIR)/* $(@D)
	cd $(@D) && ./bootstrap.sh --prefix=/usr/g++ --with-toolset=gcc --with-icu=/usr/g++
	cd $(@D) && ./bjam -sGCC_ROOT_DIRECTORY=$(GCC_ROOT) -sGCC=gcc -sGXX=g++  --v2 -d+2 -q \
		-sBUILD="release <threading>single/multi" linkflags="$(LDFLAGS)" release stage
	$(TOUCH) $@

$(INSTALL_32):  $(BUILD_32)	
	cd $(@D) && ./bjam install --prefix=$(PROTO_DIR)/usr/g++
	$(TOUCH) $@

build: $(BUILD_32)

install: $(INSTALL_32)
