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
# Copyright (c) 2010, 2015, Oracle and/or its affiliates. All rights reserved.
#

LD_Z_IGNORE =

COMPONENT_NAME=	open-fabrics
COMPONENT_VERSION=1.5.3

COMPONENT_PROJECT_URL=	http://www.openfabrics.org/
COMPONENT_BUGDB=	library/ofuv_lib utility/ofuv_tools

TPNO_OPEN_FABRICS=	3369
TPNO_IBUTILS=		5084
TPNO_INFINIBAND_DIAGS=	5085
TPNO_LIBIBMAD=		5086
TPNO_LIBIBUMAD=		5087
TPNO_LIBIBVERBS=	5082
TPNO_LIBMLX4=		5088
TPNO_LIBRDMACM=		5089
TPNO_LIBSDP=		5080
TPNO_OPENSM=		5091
TPNO_PERFTEST=		5081
TPNO_QPERF=		5083
TPNO_RDS_TOOLS=		5092

include ../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/ips.mk
include ofed.mk

# for now, everything with a Makefile should be built
SUBDIRS =	$(shell echo */Makefile | sed -e 's;/Makefile;;g')

# Do not apply the standard license transforms for this component. The
# license actions in the open-fabrics.p5m file are already tagged with the
# attributes.
LICENSE_TRANSFORMS =

.PHONY:	$(SUBDIRS)

download::		TARGET = download
unpack::		TARGET = unpack
patch::			TARGET = patch
prep::			TARGET = prep
install:		TARGET = install
clean:			TARGET = clean
clobber:		TARGET = clobber
test:			TARGET = test
parfait:		TARGET = parfait

build:		install

.DEFAULT:	publish

download unpack patch prep::	$(SUBDIRS)
install test: $(SUBDIRS)

parfait:
	$(MAKE) PARFAIT_BUILD=yes install

clean::	$(SUBDIRS)
	$(RM) -r prototype build

clobber::	$(SUBDIRS) clean

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

REQUIRED_PACKAGES += runtime/perl-512
REQUIRED_PACKAGES += runtime/perl-516
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/linker
