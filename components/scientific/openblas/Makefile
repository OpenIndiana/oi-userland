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
# Copyright (c) 2022 Niklas Poslovski
#
BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		openblas
COMPONENT_VERSION=	0.3.21
COMPONENT_FMRI=     	library/math/openblas
COMPONENT_CLASSIFICATION=Development/High Performance Computing
COMPONENT_SRC=		OpenBLAS-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.openblas.net
COMPONENT_ARCHIVE=	OpenBLAS-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f36ba3d7a60e7c8bcc54cd9aaa9b1223dd42eaf02c811791c37e8ca707c241ca
COMPONENT_ARCHIVE_URL=	http://github.com/xianyi/OpenBLAS/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=      BSD 3-Clause
COMPONENT_SUMMARY=     	Optimized BLAS library based on GotoBLAS2

# Numerical libraries should be shipped as static libs as it is still common in scientific computing projects
# See discussion here: https://github.com/OpenIndiana/oi-userland/pull/9459
DROP_STATIC_LIBRARIES= no

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# In a virtualized environment getarch cannot detect the architecture.
# It falls back to INTEL_UKNOWN which causes failure of the build.
# The option TARGET=GENERIC has to be passed to force detection.
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
                            NUM_THREADS=64 \
                            EXTRALIB=-lm

COMPONENT_INSTALL_ARGS= PREFIX=$(PROTOUSRDIR) MACHDIR=$(MACH64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
