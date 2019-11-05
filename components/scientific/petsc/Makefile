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

COMPONENT_NAME=         petsc
COMPONENT_VERSION=      3.11.3
COMPONENT_REVISION=     2
COMPONENT_SUMMARY=      PETSc - Portable, Extensible Toolkit for Scientific Computation
COMPONENT_PROJECT_URL=  http://www.mcs.anl.gov/petsc/
COMPONENT_FMRI=         library/math/petsc
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-lite-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL= \
  http://ftp.mcs.anl.gov/pub/petsc/release-snapshots/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= \
  sha256:8bee4a5ad37af85938ae755be182dcea255888b4f8b3d976bedc57e959280622
COMPONENT_LICENSE=      2-clause BSD license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_MPI_BUILD=mpich openmpi

include $(WS_MAKE_RULES)/mpi-macros.mk

PATH=$(PATH.gnu)

PKG_MACROS+= COMPONENT_MPI=$(MPI_IMPLEMENTATION)/$(MPI_COMPILER)

COMPONENT_PRE_CONFIGURE_ACTION= ($(CLONEY) $(SOURCE_DIR) $(@D))

CFLAGS+= -std=gnu99 -D_XOPEN_SOURCE=600 -D__EXTENSIONS__

CONFIG_SHELL     =
CONFIGURE_ENV    =
CONFIGURE_SCRIPT = ./configure

# Installation of external packages to destdir is not possible
CONFIGURE_OPTIONS = --prefix=$(PROTO_DIR)$(MPI_PREFIX)
CONFIGURE_OPTIONS+= --with-mpi-dir=$(MPI_PREFIX)
CONFIGURE_OPTIONS+= --with-pic
CONFIGURE_OPTIONS+= --with-debugging=0
CONFIGURE_OPTIONS+= --with-precision=double
CONFIGURE_OPTIONS+= --with-clanguage=C
CONFIGURE_OPTIONS+= --with-single-library=0
CONFIGURE_OPTIONS+= --with-shared-libraries=1
CONFIGURE_OPTIONS+= --with-fortran-interfaces=1
CONFIGURE_OPTIONS+= --PETSC_DIR=$(COMPONENT_MPI_BUILD_DIR)
CONFIGURE_OPTIONS+= --CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS+= --CXXFLAGS="$(CXXFLAGS)"
CONFIGURE_OPTIONS+= --FFLAGS="$(F77FLAGS)"
CONFIGURE_OPTIONS+= --LDFLAGS="$(LDFLAGS)"
# External packages
CONFIGURE_OPTIONS+= --download-blacs=1
CONFIGURE_OPTIONS+= --download-fblaslapack=1
CONFIGURE_OPTIONS+= --download-hypre=1
# Broken
CONFIGURE_OPTIONS+= --download-mumps=0
CONFIGURE_OPTIONS+= --download-metis=1
# Not redistributable
CONFIGURE_OPTIONS+= --download-parmetis=0
# Broken
CONFIGURE_OPTIONS+= --download-pastix=0
CONFIGURE_OPTIONS+= --download-ptscotch=1
CONFIGURE_OPTIONS+= --download-scalapack=1
CONFIGURE_OPTIONS+= --download-superlu=1
CONFIGURE_OPTIONS+= --download-suitesparse=1
# PETSc build depends on ParMETIS
CONFIGURE_OPTIONS+= --with-zoltan=0

COMPONENT_BUILD_ENV  = PETSC_DIR=$(COMPONENT_MPI_BUILD_DIR)
COMPONENT_INSTALL_ENV= PETSC_DIR=$(COMPONENT_MPI_BUILD_DIR)
COMPONENT_TEST_ENV   = PETSC_DIR=$(COMPONENT_MPI_BUILD_DIR)

# Set relative runpath to mpi directory 
PETSCLIB_RUNPATH=$(shell realpath -m --relative-to=$(MPI_LIBDIR) $(USRLIBDIR.$(BITS)))
PETSCGCC_RUNPATH=$(shell realpath -m --relative-to=$(MPI_LIBDIR) $(MPI_COMPILER_LIBDIR))

# Remove destdir to generated variables
PETSC_FILES =include/petscconf.h
PETSC_FILES+=include/petscmachineinfo.h
PETSC_FILES+=include/petscconfiginfo.h
PETSC_FILES+=lib/petsc/conf/rules
PETSC_FILES+=lib/petsc/conf/petscrules
PETSC_FILES+=lib/petsc/conf/petscvariables
PETSC_FILES+=lib/petsc/conf/modules/petsc/$(COMPONENT_VERSION)
PETSC_FILES+=lib/petsc/conf/reconfigure-arch-sunos5-c-opt.py
PETSC_FILES+=lib/petsc/conf/uninstall.py
PETSC_FILES+=lib/petsc/conf/variables
PETSC_FILES+=lib/petsc/conf/PETScBuildInternal.cmake
PETSC_FILES+=lib/pkgconfig/PETSc.pc
PETSC_FILES+=lib/pkgconfig/superlu.pc
# Each external package configuration should be processed
PETSC_FILES+=lib/petsc/conf/pkg.conf.fblaslapack
PETSC_FILES+=lib/petsc/conf/pkg.conf.hypre
PETSC_FILES+=lib/petsc/conf/pkg.conf.metis
PETSC_FILES+=lib/petsc/conf/pkg.conf.ptscotch
PETSC_FILES+=lib/petsc/conf/pkg.conf.scalapack
PETSC_FILES+=lib/petsc/conf/pkg.conf.suitesparse
PETSC_FILES+=lib/petsc/conf/pkg.conf.superlu
PETSC_FILES+=share/petsc/examples/gmakefile.test

# Fix runtime path
PETSC_LIBS =lib/libpetscmat.so.$(COMPONENT_VERSION)
PETSC_LIBS+=lib/libpetscdm.so.$(COMPONENT_VERSION)
PETSC_LIBS+=lib/libpetsctao.so.$(COMPONENT_VERSION)
PETSC_LIBS+=lib/libpetscsnes.so.$(COMPONENT_VERSION)
PETSC_LIBS+=lib/libpetscsys.so.$(COMPONENT_VERSION)
PETSC_LIBS+=lib/libpetscksp.so.$(COMPONENT_VERSION)
PETSC_LIBS+=lib/libpetscts.so.$(COMPONENT_VERSION)
PETSC_LIBS+=lib/libpetscvec.so.$(COMPONENT_VERSION)
PETSC_LIBS+=lib/libmetis.so
PETSC_LIBS+=lib/libsuperlu.so

COMPONENT_POST_INSTALL_ACTION = ( \
	$(FIND) $(PROTO_DIR)$(MPI_PREFIX) -name *.py -exec \
		$(GSED) -i -e '1 s:\#!/usr/bin/env python[0-9.]*:\#!/usr/bin/python$(PYTHON_VERSION):' {} \; ; \
	$(GSED) -i -e '1 s:\#!/usr/bin/env python[0-9.]*:\#!/usr/bin/python$(PYTHON_VERSION):' \
		$(PROTO_DIR)$(MPI_LIBDIR)/petsc/bin/petsc-performance-view ; \
	for f in $(PETSC_FILES); \
	do \
		$(GSED) -i -e 's|$(PROTO_DIR)||g' \
			-e 's|$(COMPONENT_MPI_BUILD_DIR)|$(MPI_PREFIX)|g' \
			-e 's|$(COMPONENT_DIR)|.|g' \
			$(PROTO_DIR)$(MPI_PREFIX)/$$f; \
       	done; \
	for f in $(PETSC_LIBS); \
	do \
		/usr/bin/elfedit -e 'dyn:runpath "$$ORIGIN:$$ORIGIN/$(PETSCGCC_RUNPATH):$$ORIGIN/$(PETSCLIB_RUNPATH)"' \
			$(PROTO_DIR)$(MPI_PREFIX)/$$f; \
	done; )

# DESTDIR should be removed as we install directly in the proto area
COMPONENT_INSTALL_ARGS=

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# MPI dependencies
REQUIRED_PACKAGES += library/mpich/gcc
REQUIRED_PACKAGES += library/openmpi/gcc

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += SUNWcs
