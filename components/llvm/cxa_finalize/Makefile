#
## CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#
export PARFAIT_BUILD=no
COMPILER= gcc

include ../../../make-rules/shared-macros.mk

COMPONENT_DIR := $(shell pwd)/..

COMPONENT_PRE_BUILD_ACTION = \
     ( $(MKDIR) build/$(MACH) ; \
     $(MKDIR) build/$(MACH64) )

OBJECTS = cxa_finalize-32.o cxa_finalize-64.o \
	  cxa_finalize_pic-32.o cxa_finalize_pic-64.o

include $(WS_MAKE_RULES)/common.mk

GCC_VERSION := 4.9

# We need GCC version 4.9, and not another version.
CC=/usr/gcc/$(GCC_VERSION)/bin/gcc
CXX=/usr/gcc/$(GCC_VERSION)/bin/g++

RELEASE_LIST=Debug+Asserts+Checks Debug+Asserts Debug Release+Debug Release Unoptimized

# Keep CFLAGS simple and generic.
CFLAGS = -g -O2 -std=c99 -Wall -Wextra -Wcast-align
ARCH = $(shell uname -p)

ifeq ($(ARCH),sparc)
  CFLAGS += -mtune=ultrasparc -mcpu=ultrasparc -mvis
endif

ifeq ($(ARCH),i386)
  CFLAGS += -mtune=opteron -march=opteron -mno-sse3 -mno-ssse3
endif

all:: $(OBJECTS)

cxa_finalize-32.o: cxa_finalize.c
	$(CC) -m32 $(CFLAGS) -c $< -o $@

cxa_finalize_pic-32.o: cxa_finalize.c
	$(CC) -m32 $(CFLAGS) -fPIC -c $< -o $@

cxa_finalize-64.o: cxa_finalize.c
	$(CC) -m64 $(CFLAGS) -c $< -o $@

cxa_finalize_pic-64.o: cxa_finalize.c
	$(CC) -m64 $(CFLAGS) -fPIC -c $< -o $@

cxa_atexit-32.o: cxa_atexit.c
	$(CC) -m32 $(CFLAGS) -c $< -o $@

cxa_atexit-64.o: cxa_atexit.c
	$(CC) -m64 $(CFLAGS) -c $< -o $@

clean::
	rm -f $(OBJECTS)

check::	build
	$(MKDIR) build/$(MACH)
	$(MKDIR) build/$(MACH64)

build: all

install: build
	$(MKDIR) $(PROTOUSRLIBDIR)/clang
	$(MKDIR) $(PROTOUSRLIBDIR)/clang/$(MACH64)
	$(CP) cxa_finalize-32.o \
	  $(PROTOUSRLIBDIR)/clang/cxa_finalize.o
	$(CP) cxa_finalize_pic-32.o \
	  $(PROTOUSRLIBDIR)/clang/cxa_finalize_pic.o
	$(CP) cxa_finalize-64.o \
	  $(PROTOUSRLIBDIR)/clang/$(MACH64)/cxa_finalize.o
	$(CP) cxa_finalize_pic-64.o \
	  $(PROTOUSRLIBDIR)/clang/$(MACH64)/cxa_finalize_pic.o
	list='$(RELEASE_LIST)'; for f in $$list; do \
	     if test -d $(BUILD_DIR_32)/$$f/lib ; then \
	     echo "Installing cxa_finalize in $(BUILD_DIR_32)/$$f/lib..." ; \
	     $(MKDIR)  $(BUILD_DIR_32)/$$f/lib/$(MACH64) ; \
	     $(CP) cxa_finalize-32.o \
	     $(BUILD_DIR_32)/$$f/lib/cxa_finalize.o ; \
	     $(CP) cxa_finalize_pic-32.o \
	     $(BUILD_DIR_32)/$$f/lib/cxa_finalize_pic.o ; \
	     $(CP) cxa_finalize-64.o \
	     $(BUILD_DIR_32)/$$f/lib/$(MACH64)/cxa_finalize.o ; \
	     $(CP) cxa_finalize_pic-64.o \
	     $(BUILD_DIR_32)/$$f/lib/$(MACH64)/cxa_finalize_pic.o ; \
	     fi ; \
	     if test -d $(BUILD_DIR_64)/$$f/lib ; then \
	     echo "Installing cxa_finalize in $(BUILD_DIR_64)/$$f/lib..." ; \
	     $(MKDIR)  $(BUILD_DIR_64)/$$f/lib/$(MACH64) ; \
	     $(CP) cxa_finalize-32.o \
	     $(BUILD_DIR_64)/$$f/lib/cxa_finalize.o ; \
	     $(CP) cxa_finalize_pic-32.o \
	     $(BUILD_DIR_64)/$$f/lib/cxa_finalize_pic.o ; \
	     $(CP) cxa_finalize-64.o \
	     $(BUILD_DIR_64)/$$f/lib/$(MACH64)/cxa_finalize.o ; \
	     $(CP) cxa_finalize_pic-64.o \
	     $(BUILD_DIR_64)/$$f/lib/$(MACH64)/cxa_finalize_pic.o ; \
	     fi ; \
	     done

test: $(NO_TESTS)

system-test: $(NO_TESTS)

