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
# Copyright (c) 2013, Aurelien Larcher. All rights reserved.
#

include $(WS_MAKE_RULES)/shared-macros.mk

MPI.mpich =         mpich

MPICC.mpich =       mpicc
MPICXX.mpich =      mpicxx
MPIF77.mpich =      mpif77
MPIFC.mpich =       mpif90

MPI.openmpi =       openmpi

# Default to mpich
MPI_IMPLEMENTATION ?= $(MPI.mpich)
MPI_COMPILER = $(COMPILER)

MPI_BUNDLE =        $(MPI_IMPLEMENTATION)-$(MPI_COMPILER)

MPI_PREFIX =        $(USRLIBDIR)/$(MPI_IMPLEMENTATION)/$(MPI_COMPILER)

CONFIGURE_DEFAULT_DIRS=no

MPI_BINDIR.32 =     $(MPI_PREFIX)/bin
MPI_BINDIR.64 =     $(MPI_PREFIX)/bin/$(MACH64)
MPI_BINDIR    =     $(MPI_BINDIR.$(BITS))

MPI_SBINDIR.32 =     $(MPI_PREFIX)/sbin
MPI_SBINDIR.64 =     $(MPI_PREFIX)/sbin/$(MACH64)
MPI_SBINDIR    =     $(MPI_SBINDIR.$(BITS))

MPI_LIBDIR.32 =     $(MPI_PREFIX)/lib
MPI_LIBDIR.64 =     $(MPI_PREFIX)/lib/$(MACH64)
MPI_LIBDIR =        $(MPI_LIBDIR.$(BITS))

MPI_ETCDIR =        $(MPI_PREFIX)/etc

MPI_INCDIR =        $(USRINCDIR)/$(MPI_IMPLEMENTATION)

MPI_SHAREDIR =      $(USRSHAREDIR)
MPI_DATADIR =       $(MPI_SHAREDIR)/$(MPI_IMPLEMENTATION)
MPI_DOCDIR =        $(USRSHAREDOCDIR)/$(MPI_IMPLEMENTATION)
MPI_HTMLDIR =       $(USRSHAREDOCDIR)/www
MPI_MANDIR =        $(USRSHAREMANDIR)


