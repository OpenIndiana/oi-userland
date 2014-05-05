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

COMPONENT_NAME= clang
LLVM_NAME=llvm
CLANG_NAME=cfe

COMPONENT_VERSION= 3.3
COMPONENT_SUMMARY= LLVM tools and Clang compiler
COMPONENT_SRC= $(LLVM_NAME)-$(COMPONENT_VERSION).src
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:68766b1e70d05a25e2f502e997a3cb3937187a3296595cf6e0977d5cd6727578
COMPONENT_ARCHIVE_URL= \
  http://llvm.org/releases/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://llvm.org/

COMPONENT_ARCHIVE_1=    $(CLANG_NAME)-$(COMPONENT_VERSION).src.tar.gz
COMPONENT_ARCHIVE_HASH_1= \
    sha256:b1b55de4ab3a57d3e0331a83e0284610191c77d924e3446498d9113d08dfb996
COMPONENT_ARCHIVE_URL_1= http://llvm.org/releases/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE_1)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_PREFIX= /usr/clang/$(COMPONENT_VERSION)

PATH=/usr/sbin:/usr/bin:/usr/perl5/bin

COMPONENT_POST_UNPACK_ACTION += $(UNPACK) $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1) && \
	mv $(CLANG_NAME)-$(COMPONENT_VERSION).src $(COMPONENT_SRC)/tools/clang

COMPONENT_PRE_CONFIGURE_ACTION =        (cp -a $(SOURCE_DIR)/* $(@D))

COMPONENT_POST_INSTALL_ACTION =  for file in `echo $(PROTO_DIR)/usr/clang/$(COMPONENT_VERSION)/bin/*`; do \
 					 elfedit -e 'dyn:runpath $$ORIGIN/../lib' $$file ; \
				done && \
				for file in `echo $(PROTO_DIR)/usr/clang/$(COMPONENT_VERSION)/lib/*.so`; do \
				  elfedit -e 'dyn:delete RUNPATH' $$file ; \
				  elfedit -e 'dyn:delete RPATH' $$file ; \
				done

build: $(BUILD_32)

install: $(INSTALL_32)
