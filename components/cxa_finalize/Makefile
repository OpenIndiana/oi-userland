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
# Copyright 2013 Andrzej Szeszo.  All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME= cxa_finalize
LIBCXXRT_COMMIT=c88684021db880d3cc9e2bf3da848419fdd41be9
LIBCXXRT_NAME=libcxxrt
LIBCXXRT_SRC=$(LIBCXXRT_NAME)-$(LIBCXXRT_COMMIT).zip

COMPONENT_VERSION= 0.1
COMPONENT_SUMMARY= PathScale libcxxrt components
COMPONENT_SRC= $(LIBCXXRT_NAME)-$(LIBCXXRT_COMMIT)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:9b33e8d979e6afefb93d74d5d9cda79e492ecca08db8d2e95a529ce233c1cbf1
COMPONENT_ARCHIVE_URL= \
  https://github.com/pathscale/libcxxrt/archive/$(LIBCXXRT_COMMIT).zip
COMPONENT_PROJECT_URL = https://github.com/pathscale/

include ../../make-rules/prep.mk
include ../../make-rules/ips.mk

CONFIGURE_PREFIX= /usr/llvm/$(COMPONENT_VERSION)

PATH=/usr/sbin:/usr/bin:/usr/perl5/bin


build: $(BUILD_32)

$(BUILD_32):$(SOURCE_DIR)/.prep
	cd $(LIBCXXRT_NAME)-$(LIBCXXRT_COMMIT)/src && \
	$(CC) -std=c99 -m32 -c cxa_atexit.c -o cxa_atexit.32.o && \
	$(CC) -std=c99 -m32 -c cxa_finalize.c  -o cxa_finalize.32.o && \
	/usr/ccs/bin/ld -r cxa_finalize.32.o cxa_atexit.32.o -o cxa_finalize_tg.32.o  && \
	$(CC) -std=c99 -m64 -c cxa_atexit.c -o cxa_atexit.64.o && \
	$(CC) -std=c99 -m64 -c cxa_finalize.c  -o cxa_finalize.64.o && \
	/usr/ccs/bin/ld -r cxa_finalize.64.o cxa_atexit.64.o -o cxa_finalize_tg.64.o && \
	( [ -d $(BUILD_DIR_32) ] || mkdir -p $(BUILD_DIR_32) ) &&\
	touch $(BUILD_32)
		

#  $(COMPONENT_DIR)/../gcc47-libgmp/build/$(MACH32)/.installed \
#  $(COMPONENT_DIR)/../gcc47-libmpc/build/$(MACH32)/.installed \
#  $(COMPONENT_DIR)/../gcc47-libmpfr/build/$(MACH32)/.installed \
#  $(BUILD_32)

install: $(INSTALL_32)

$(INSTALL_32): $(BUILD_32)
	mkdir -p $(PROTO_DIR)/usr/lib && \
	mkdir -p $(PROTO_DIR)/usr/lib/amd64 && \
	cd $(LIBCXXRT_NAME)-$(LIBCXXRT_COMMIT)/src && \
	cp cxa_finalize_tg.32.o $(PROTO_DIR)/usr/lib/cxa_finalize.o && \
	cp cxa_finalize_tg.64.o $(PROTO_DIR)/usr/lib/amd64/cxa_finalize.o && \
	touch $(INSTALL_32)
