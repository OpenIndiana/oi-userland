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
# Copyright 2015 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           workspace-patterns
COMPONENT_VERSION=        7.5
COMPONENT_FMRI=           x11/data/workspace-patterns
COMPONENT_CLASSIFICATION= System/X11
COMPONENT_SUMMARY=  		Bitmap patterns for workspace backgrounds
COMPONENT_SRC=      		src
COMPONENT_PROJECT_URL = https://hg.java.net/hg/solaris-x11~x-s12-clone
COMPONENT_LICENSE=      Oracle
COMPONENT_LICENSE_FILE= workspace-patterns.license

include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

PATTERN_FILES = \
	attributes \
	background.xbm \
	bricks.xbm \
	burl.xbm \
	corn.xbm \
	dmndpla.xbm \
	dolphin.xbm \
	dotwave2.xbm \
	dune.xbm \
	flowers.xbm \
	flyseye.xbm \
	foreground.xbm \
	fuji.xbm \
	geiger2.xbm \
	gray25.xbm \
	gray50.xbm \
	gray75.xbm \
	miniweave.xbm \
	sbump.xbm \
	sizmk2.xbm \
	southwest.xbm \
	squares.xbm \
	sunmulti.xbm \
	swirl2.xbm \
	wave1.xbm	\
	wrnkle2.xbm
	
PATTERN_DIR=$(USRSHAREDIR)/patterns

download:

build:

install:
	$(MKDIR) $(PROTO_DIR)$(PATTERN_DIR)
	cd $(COMPONENT_DIR)/src \
		&& $(INSTALL) -t $(PROTO_DIR)$(PATTERN_DIR) $(PATTERN_FILES) 

test: $(NO_TESTS)


