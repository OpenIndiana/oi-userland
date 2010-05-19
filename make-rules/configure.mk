#
# CDDL HEADER START
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
# Copyright (c) 2010, Oracle and/or it's affiliates.  All rights reserved.
#

#
# Rules and Macros for building opens source software that uses configure /
# GNU auto* tools to configure their build for the system they are on.  This
# uses GNU Make to build the components to take advantage of the viewpath
# support and build multiple version (32/64 bit) from a shared source.
#
# To use these rules, include ../make-rules/configure.mk in your Makefile
# and define "build", "install" targets appropriate to building your component.
# Ex:
#
# 	build:		$(COMPONENT_SRC)/build-$(MACH32)/.built \
#	 		$(COMPONENT_SRC)/build-$(MACH64)/.built
# 
#	install:	$(COMPONENT_SRC)/build-$(MACH32)/.installed \
#	 		$(COMPONENT_SRC)/build-$(MACH64)/.installed
#
# Any additional pre/post configure, build, or install actions can be specified
# in your make file by setting them in on of the following macros:
#	COMPONENT_PRE_CONFIGURE_ACTION, COMPONENT_POST_CONFIGURE_ACTION
#	COMPONENT_PRE_BUILD_ACTION, COMPONENT_POST_BUILD_ACTION
#	COMPONENT_PRE_INSTALL_ACTION, COMPONENT_POST_INSTALL_ACTION
#
# If component specific make targets need to be used for build or install, they
# can be specified in
#	COMPONENT_BUILD_TARGETS, COMPONENT_INSTALL_TARGETS
#

CONFIG_SHELL =	/bin/bash

CONFIGURE_OPTIONS += --prefix=/usr
CONFIGURE_OPTIONS += CC="$(CC)"
CONFIGURE_OPTIONS += CXX="$(CCC)"
CONFIGURE_OPTIONS.32 += --bindir=/usr/bin
CONFIGURE_OPTIONS.32 += --libdir=/usr/lib
CONFIGURE_OPTIONS.64 = --bindir=/usr/bin/$(MACH64)
CONFIGURE_OPTIONS.64 += --libdir=/usr/lib/$(MACH64)

$(COMPONENT_SRC)/build-$(MACH32)/.configured:	BITS=32
$(COMPONENT_SRC)/build-$(MACH64)/.configured:	BITS=64

CONFIGURE_OPTIONS += $(CONFIGURE_OPTIONS.$(BITS))

# set the default target for installation of the component
COMPONENT_INSTALL_TARGETS =	install

# configure the unpacked source for building 32 and 64 bit version
$(COMPONENT_SRC)/build-%/.configured:	$(COMPONENT_SRC)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(@D) ; env - $(CONFIGURE_ENV) $(CONFIG_SHELL) \
		../configure $(CONFIGURE_OPTIONS) $(CONFIGURE_OPTIONS.$(BITS)))
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@

# build the configured source
$(COMPONENT_SRC)/build-%/.built:	$(COMPONENT_SRC)/build-%/.configured
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; $(COMPONENT_BUILD_ENV) $(GMAKE) $(COMPONENT_BUILD_TARGETS))
	$(COMPONENT_POST_BUILD_ACTION)
	$(TOUCH) $@

# install the built source into a prototype area
$(COMPONENT_SRC)/build-%/.installed:	$(COMPONENT_SRC)/build-%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(@D) ; $(COMPONENT_INSTALL_ENV) $(GMAKE) \
			DESTDIR=$(PROTO_DIR) $(COMPONENT_INSTALL_TARGETS))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@
