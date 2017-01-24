#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Aurelien Larcher
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           zoltan
COMPONENT_VERSION=        3.83
COMPONENT_SUMMARY=        ZOLTAN - Parallel Partitioning, Load Balancing and Data-Management Services
COMPONENT_PROJECT_URL=    http://www.cs.sandia.gov/zoltan/
COMPONENT_FMRI=           library/math/zoltan
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_SRC=            Zoltan_v$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=    http://www.cs.sandia.gov/~kddevin/Zoltan_Distributions/zoltan_distrib_v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:d0d78fdeab7a385c87d3666b8a8dc748994ff04d3fd846872a4845e12d79c1bb
COMPONENT_LICENSE=        BSD

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_MPI_BUILD=mpich openmpi

include $(WS_MAKE_RULES)/mpi-macros.mk

CC = $(MPICC)
CXX= $(MPICXX)
F77= $(MPIF77)
FC = $(MPIFC)

CONFIGURE_DEFAULT_DIRS=no
CONFIGURE_PREFIX=$(MPI_PREFIX)

CONFIGURE_OPTIONS+= --includedir=$(USRINCDIR)/zoltan
CONFIGURE_OPTIONS+= --libdir=$(MPI_LIBDIR)

CONFIGURE_OPTIONS+= --enable-f90interface
CONFIGURE_OPTIONS+= --enable-zoltan-cppdriver
CONFIGURE_OPTIONS+= --enable-mpi
CONFIGURE_OPTIONS+= --enable-zoltan-tests
CONFIGURE_OPTIONS+= --enable-zoltan-examples

# MPI specifics
CONFIGURE_OPTIONS+= --with-mpi=$(MPI_PREFIX)
CONFIGURE_OPTIONS+= --with-mpi-incdir=$(MPI_INCDIR)
CONFIGURE_OPTIONS+= --with-mpi-libdir=$(MPI_LIBDIR)


build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Added manually
REQUIRED_PACKAGES += library/mpich/gcc
REQUIRED_PACKAGES += library/openmpi/gcc

