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

#
# Copyright (c) 2010, 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk
#libreadline.so needs libcurses.so, but -z ignore will not leave a dependency.
LD_Z_IGNORE=

COMPONENT_NAME=		gnuplot
COMPONENT_VERSION=	4.4.0
IPS_PKG_NAME=           image/gnuplot
COMPONENT_DESCRIPTION=  "gnuplot - command-driven interactive function plotting program (4.4.0)"
COMPONENT_CLASSIFICATION="Applications/Graphics and Imaging"
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://gnuplot.info/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha1:04a2eede7b2af8e64144aa8ffede6535b7a043b5
COMPONENT_ARCHIVE_URL=  http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_NAME)/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download

COMPONENT_BUILD_TARGETS = all info install-am

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CFLAGS += -xnorunpath -Bdirect
CXXFLAGS += -norunpath -Bdirect

CONFIGURE_OPTIONS  += --libexecdir=/usr/lib
CONFIGURE_OPTIONS  += --sysconfdir=/etc/gnu
CONFIGURE_OPTIONS  += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS  += CXXFLAGS="$(CXXFLAGS)"

include ../../make-rules/shared-targets.mk

# common targets
build:		$(BUILD_32)

install: build $(INSTALL_32) install_demo

# The Gnuplot Makefiles do not ship the demo files.

DEMO_FILES = *.bin *.cfg *.cor *.dat *.dem *.edf \
    *.fnc *.inc nearmap.csv *.pdb *.r3d *.rgb *.png sound.par sound2.par \
    start.par *.rot gnu-valley random-points gpdemos.tcl
DEMO_BINARIES = binary[123]
DEMO_SCRIPTS = rundemo runtcldemo
PROTODEMODIR = $(PROTOUSRDIR)/demo/gnuplot

install_demo:
	mkdir -p $(PROTODEMODIR)
	@(p=`pwd` && \
	    echo "+ cd $(SOURCE_DIR)/demo" && \
	    cd $(SOURCE_DIR)/demo && \
	    for file in $(DEMO_FILES); \
	    do \
	    echo "+ cp -p $$file $(PROTODEMODIR)"; \
	    cp -p $$file $(PROTODEMODIR); \
	    done && \
	    echo "+ cd $$p")
	@(p=`pwd` && \
	    echo "+ cd $(BUILD_DIR_32)/demo" && \
	    cd $(BUILD_DIR_32)/demo && \
	    for file in $(DEMO_BINARIES); \
	    do \
	    echo "+ cp -p $$file $(PROTODEMODIR)"; \
	    cp -p $$file $(PROTODEMODIR); \
	    done && \
	    echo "+ cd $$p")
	@(p=`pwd` && \
	    echo "+ cd $(COMPONENT_DIR)" && \
	    cd $(COMPONENT_DIR) && \
	    for file in $(DEMO_SCRIPTS); \
	    do \
	    echo "+ cp -p $$file $(PROTODEMODIR)"; \
	    cp -p $$file $(PROTODEMODIR); \
	    done && \
	    echo "+ cd $$p")

test: build
	@cd $(BUILD_DIR_32); $(MAKE) check

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk



