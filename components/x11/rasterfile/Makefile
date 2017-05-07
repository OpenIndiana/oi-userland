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

COMPONENT_NAME=           rasterfile
COMPONENT_VERSION=        7.5
COMPONENT_FMRI=           x11/header/rasterfile
COMPONENT_CLASSIFICATION= Development/X11
COMPONENT_SUMMARY=  			rasterfile - Sun file format for raster images
COMPONENT_SRC=						src
COMPONENT_PROJECT_URL = 	https://hg.java.net/hg/solaris-x11~x-s12-clone
COMPONENT_LICENSE=      	Oracle
COMPONENT_LICENSE_FILE= 	rasterfile.license

include $(WS_TOP)/make-rules/ips.mk

rasterfile_INCDIR=$(PROTO_DIR)$(USRINCDIR)/pixrect
rasterfile_MANDIR=$(PROTO_DIR)$(USRSHAREMAN5DIR)

download:

build:

install:
	$(MKDIR) $(rasterfile_INCDIR) $(rasterfile_MANDIR)
	$(INSTALL) -m 0444 $(SOURCE_DIR)/rasterfile.h $(rasterfile_INCDIR)
	$(INSTALL) -m 0444 $(SOURCE_DIR)/rasterfile.5 $(rasterfile_MANDIR)

test: $(NO_TESTS)


