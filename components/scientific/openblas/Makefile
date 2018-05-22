#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.illumos.org/license/CDDL.
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
# Copyright (c) 2014-2017, Aurelien Larcher. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openblas
COMPONENT_VERSION=	0.2.19
COMPONENT_VERSION_REV=	0
COMPONENT_VERSION_TAG=	ga7126c2
COMPONENT_REVISION_TAG= 9a7e0ec
COMPONENT_FMRI=     	library/math/openblas
COMPONENT_CLASSIFICATION=Development/High Performance Computing
COMPONENT_SRC=		xianyi-OpenBLAS-$(COMPONENT_REVISION_TAG)
COMPONENT_PROJECT_URL=	http://www.openblas.net
COMPONENT_ARCHIVE=	xianyi-OpenBLAS-v$(COMPONENT_VERSION)-$(COMPONENT_VERSION_REV)-$(COMPONENT_VERSION_TAG).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:878353b52940e0d5be32011cd5ba8440758f5270c3fa0f6f6200c26eabc53f1c
COMPONENT_ARCHIVE_URL=	http://github.com/xianyi/OpenBLAS/tarball/v$(COMPONENT_VERSION)
COMPONENT_LICENSE=      BSD 3-Clause
COMPONENT_SUMMARY=     	Optimized BLAS library based on GotoBLAS2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

# In a virtualized environment getarch cannot detect the architecture.
# It falls back to INTEL_UKNOWN which causes failure of the build.
# The option TARGET=GENERIC has to be passed to force detection.
# Do not define NO_STATIC nor NO_SHARED to build both libraries
COMPONENT_BUILD_GMAKE_ARGS= PREFIX=$(USRDIR) \
                            DYNAMIC_ARCH=1 \
                            TARGET=PRESCOTT \
                            BINARY=$(BITS) \
                            CROSS_SUFFIX="" \
                            FC=$(FC) CC=$(CC) \
                            COMMON_OPT="$(CFLAGS) -Wa,--divide" \
                            NO_LAPACKE=1 \
                            USE_OPENMP=0 \
                            USE_THREAD=1 \
                            NUM_THREADS=64

MACHDIR.32=
MACHDIR.64=$(MACH64)

COMPONENT_INSTALL_ARGS= PREFIX=$(PROTOUSRDIR) MACHDIR=$(MACHDIR.$(BITS)) 

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GFORTRAN_RUNTIME_PKG)
