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
# Copyright (c) 2010, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/ips.mk
include ofed.mk

LD_Z_IGNORE =

COMPONENT_NAME=	open-fabrics
COMPONENT_VERSION=1.5.3

COMPONENT_PROJECT_URL=	http://www.openfabrics.org/
COMPONENT_BUGDB=	library/ofuv_lib utility/ofuv_tools

# for now, everything with a Makefile should be built
SUBDIRS =	$(shell echo */Makefile | sed -e 's;/Makefile;;g')

# Do not apply the standard license transforms for this component. The
# license actions in the open-fabrics.p5m file are already tagged with the
# attributes.
LICENSE_TRANSFORMS =

.PHONY:	$(SUBDIRS)

download:		TARGET = download
prep:			TARGET = prep
install:		TARGET = install
clean:			TARGET = clean
clobber:		TARGET = clobber
test:			TARGET = test

build:		install

.DEFAULT:	publish

download prep install test: $(SUBDIRS)

clean:	$(SUBDIRS)
	$(RM) -r prototype build

clobber:	$(SUBDIRS) clean

$(SUBDIRS):	FORCE
	@cd $@ && echo "$(TARGET) $@" && $(MAKE) $(TARGET)

# declare module dependencies
librdmacm:		libibverbs
libmlx4:		libibverbs
rds-tools:		libibverbs
perftest:		libibverbs librdmacm libibverbs
qperf:			libibverbs librdmacm
libibumad:		libibverbs
libibmad:		libibumad
opensm:			libibumad libibmad
ibutils:		opensm
infiniband-diags:	libibverbs opensm

FORCE:
