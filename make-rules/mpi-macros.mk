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
# Copyright (c) 2013-2017, Aurelien Larcher. All rights reserved.
#

MPI_IMPLEMENTATIONS_LIST = mpich openmpi

# Define compilers
MPI.mpich =         mpich

MPICC.mpich =       mpicc
MPICXX.mpich =      mpicxx
MPIF77.mpich =      mpif77
MPIFC.mpich =       mpif90

MPI.openmpi =       openmpi

MPICC.openmpi =     mpicc
MPICXX.openmpi =    mpicxx
MPIF77.openmpi =    mpif77
MPIFC.openmpi =     mpif90

# Default to mpich
MPI_IMPLEMENTATION ?= $(MPI.mpich)

MPICC =             $(MPICC.$(MPI_IMPLEMENTATION))
MPICXX =            $(MPICXX.$(MPI_IMPLEMENTATION))
MPIF77 =            $(MPIF77.$(MPI_IMPLEMENTATION))
MPIFC =             $(MPIFC.$(MPI_IMPLEMENTATION))

# Define compiler enviromnent
MPI_COMPILER = $(COMPILER)
MPI_COMPILER_ROOT=
MPI_COMPILER_LIBDIR=

ifeq ($(strip $(MPI_COMPILER)),gcc)

MPI_COMPILER_ROOT=$(GCC_ROOT)
MPI_COMPILER_LIBDIR=$(MPI_COMPILER_ROOT)/lib/$(ARCHLIBSUBDIR$(BITS))

endif

# Define implementation specific paths
MPI_BUNDLE =        $(MPI_IMPLEMENTATION)-$(MPI_COMPILER)

MPI_PREFIX.32 =     $(USRLIBDIR)/$(MPI_IMPLEMENTATION)/$(MPI_COMPILER)
MPI_PREFIX.64 =     $(USRLIBDIR64)/$(MPI_IMPLEMENTATION)/$(MPI_COMPILER)
MPI_PREFIX    =	    $(MPI_PREFIX.$(BITS))

MPI_BINDIR.32 =     $(MPI_PREFIX.32)/bin
MPI_BINDIR.64 =     $(MPI_PREFIX.64)/bin
MPI_BINDIR    =     $(MPI_BINDIR.$(BITS))

MPI_SBINDIR.32 =     $(MPI_PREFIX.32)/sbin
MPI_SBINDIR.64 =     $(MPI_PREFIX.64)/sbin
MPI_SBINDIR    =     $(MPI_SBINDIR.$(BITS))

MPI_LIBDIR.32 =     $(MPI_PREFIX.32)/lib
MPI_LIBDIR.64 =     $(MPI_PREFIX.64)/lib
MPI_LIBDIR    =     $(MPI_LIBDIR.$(BITS))

MPI_ETCDIR.32 =     $(MPI_PREFIX.32)/etc
MPI_ETCDIR.64 =     $(MPI_PREFIX.64)/etc
MPI_ETCDIR    =     $(MPI_ETCDIR.$(BITS))

MPI_INCDIR =        $(USRINCDIR)/$(MPI_IMPLEMENTATION)

MPI_SHAREDIR =      $(USRSHAREDIR)
MPI_DATADIR  =      $(MPI_SHAREDIR)/$(MPI_IMPLEMENTATION)
MPI_DOCDIR   =      $(USRSHAREDOCDIR)/$(MPI_IMPLEMENTATION)
MPI_HTMLDIR  =      $(USRSHAREDOCDIR)/www
MPI_MANDIR   =      $(USRSHAREMANDIR)


# Create meta rule to trigger build for each listed implementation

ifneq ($(strip $(COMPONENT_MPI_BUILD)),)

$(BUILD_DIR_32)/%/.configured:	BITS=32
$(BUILD_DIR_64)/%/.configured:	BITS=64

$(BUILD_DIR_32)/%/.built:	BITS=32
$(BUILD_DIR_64)/%/.built:	BITS=64

BUILD_32=
BUILD_64=

$(BUILD_DIR_32)/%/.installed: BITS=32
$(BUILD_DIR_64)/%/.installed: BITS=64

INSTALL_32=
INSTALL_64=

$(BUILD_DIR_32)/%/.tested:		BITS=32
$(BUILD_DIR_64)/%/.tested:		BITS=64

$(BUILD_DIR_32)/%/.tested-and-compared:		BITS=32
$(BUILD_DIR_64)/%/.tested-and-compared:		BITS=64

TEST_32=
TEST_64=

define mpi-rule

BUILD_DIR_32_$(1) =	$$(BUILD_DIR)/$$(MACH32)/$(1)
BUILD_DIR_64_$(1) =	$$(BUILD_DIR)/$$(MACH64)/$(1)

$(BUILD_DIR)/%/$(1)/.configured:  MPI_IMPLEMENTATION=$(1)

$(BUILD_DIR)/%/$(1)/.built:       MPI_IMPLEMENTATION=$(1)

BUILD_32+= $$(BUILD_DIR_32_$(1))/.built
BUILD_64+= $$(BUILD_DIR_64_$(1))/.built

$(BUILD_DIR)/%/$(1)/.installed:   MPI_IMPLEMENTATION=$(1)

INSTALL_32+= $$(BUILD_DIR_32_$(1))/.installed
INSTALL_64+= $$(BUILD_DIR_64_$(1))/.installed

$(BUILD_DIR)/%/$(1)/.tested:      MPI_IMPLEMENTATION=$(1)

$(BUILD_DIR)/%/$(1)/.tested-and-compared:      MPI_IMPLEMENTATION=$(1)

ifeq ($(strip $(wildcard $(COMPONENT_TEST_RESULTS_DIR)/results-*.master)),)
TEST_32+= $$(BUILD_DIR_32_$(1))/.tested
TEST_64+= $$(BUILD_DIR_64_$(1))/.tested
else
TEST_32+= $$(BUILD_DIR_32_$(1))/.tested-and-compared 
TEST_64+= $$(BUILD_DIR_64_$(1))/.tested-and-compared
endif

endef

$(foreach mpi, $(COMPONENT_MPI_BUILD), $(eval $(call mpi-rule,$(mpi))))

endif

COMPONENT_MPI_BUILD_DIR= $(BUILD_DIR_$(BITS)_$(MPI_IMPLEMENTATION))
