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
# Copyright (c) 2010, 2016, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

LD_Z_IGNORE =

COMPONENT_NAME=	open-fabrics
COMPONENT_VERSION=3.18
COMPONENT_SRC=

COMPONENT_PROJECT_URL=	http://www.openfabrics.org/
COMPONENT_BUGDB=	library/ofuv_lib

TPNO_IBUTILS=		24918   
TPNO_INFINIBAND_DIAGS=	24917   
TPNO_LIBIBMAD=		24856   
TPNO_LIBIBUMAD=		24914   
TPNO_LIBIBVERBS=	25232   
TPNO_LIBMLX4=		25233
TPNO_LIBRDMACM=		25227   
TPNO_OPENSM=		24915
TPNO_QPERF=		24916
TPNO_LIBSDP=		5080
TPNO_PERFTEST=		5081
TPNO_RDS_TOOLS=		5092

include libsif/libsif-macros.mk 

PKG_MACROS +=  LIBSIF_COMPONENT_VERSION=$(LIBSIF_COMPONENT_VERSION)
PKG_MACROS +=  LIBSIF_COMPONENT_ARCHIVE_URL=$(LIBSIF_COMPONENT_ARCHIVE_URL)

# sensitive to kernel interface changes.
ifeq ($(BUILD_TYPE), evaluation)
PUBLISH_STAMP=
SUBDIRS =
else
# for now, everything with a Makefile should be built
SUBDIRS =	$(shell echo */Makefile | sed -e 's;/Makefile;;g')
endif

include ofed.mk
include $(WS_MAKE_RULES)/ips.mk

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
system-test:		TARGET = system-test
parfait:		TARGET = parfait

build:		install

.DEFAULT:	publish

download unpack patch prep::	$(SUBDIRS)
install test system-test: $(SUBDIRS)

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
perftest:		libibverbs librdmacm
qperf:			libibverbs librdmacm
libibumad:		libibverbs
libibmad:		libibumad
opensm:			libibumad libibmad
ibutils:		opensm
infiniband-diags:	libibverbs opensm
libsif: 		libibverbs

FORCE:

REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/gcc/gcc-c++-runtime
REQUIRED_PACKAGES += system/library/math
