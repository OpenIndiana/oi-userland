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
# Copyright 2013-2018 Aurelien Larcher.  All rights reserved.
# Copyright 2023 Klaus Ziegler
#

USE_DEFAULT_TEST_TRANSFORMS = yes
include ../../../make-rules/shared-macros.mk
MPI_IMPLEMENTATION  = openmpi
include $(WS_MAKE_RULES)/mpi-macros.mk

COMPONENT_NAME =            openmpi/$(COMPILER)
OPENMPI_VERSION_MAJOR =     4.1
COMPONENT_VERSION =         $(OPENMPI_VERSION_MAJOR).7
COMPONENT_SUMMARY =         OpenMPI - High Performance Message Passing Library
COMPONENT_PROJECT_URL =     https://www.open-mpi.org
COMPONENT_SRC_NAME =        openmpi
COMPONENT_SRC =             $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE =         $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH =    sha256:3956daf86e8b570e31155d92ed4b2b1699bc36455ae24a0d98ca376d3e8b4e9d
COMPONENT_ARCHIVE_URL =     https://www.open-mpi.org/software/ompi/v$(OPENMPI_VERSION_MAJOR)/downloads/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI =            library/openmpi/$(COMPILER)
COMPONENT_CLASSIFICATION =  Development/High Performance Computing
COMPONENT_LICENSE      =    BSD 2-Clause
COMPONENT_LICENSE_FILE =    LICENSE

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# gcc 14 complains about this
CFLAGS += -Wno-error=implicit-function-declaration
CFLAGS += -Wno-error=incompatible-pointer-types

CONFIGURE_PREFIX= $(MPI_PREFIX)

CONFIGURE_OPTIONS += --bindir=$(MPI_BINDIR)
CONFIGURE_OPTIONS += --datadir=$(MPI_DATADIR)
CONFIGURE_OPTIONS += --docdir=$(MPI_DOCDIR)
CONFIGURE_OPTIONS += --htmldir=$(MPI_HTMLDIR)
CONFIGURE_OPTIONS += --includedir=$(MPI_INCDIR)
CONFIGURE_OPTIONS += --libdir=$(MPI_LIBDIR)
CONFIGURE_OPTIONS += --mandir=$(MPI_MANDIR)
CONFIGURE_OPTIONS += --sbindir=$(MPI_SBINDIR)
CONFIGURE_OPTIONS += --sysconfdir=$(MPI_ETCDIR)
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --enable-mpi-fortran=usempi
CONFIGURE_OPTIONS += --enable-mpi-cxx
CONFIGURE_OPTIONS += --enable-mpi-cxx-seek
CONFIGURE_OPTIONS += --disable-event-epoll
CONFIGURE_OPTIONS += --with-package-string=Openindiana
CONFIGURE_OPTIONS += --with-wrapper-cflags="$(CC_BITS) -L$(MPI_LIBDIR) -R$(MPI_LIBDIR)"
CONFIGURE_OPTIONS += --with-wrapper-cxxflags="$(CC_BITS) -L$(MPI_LIBDIR) -R$(MPI_LIBDIR)"
CONFIGURE_OPTIONS += --with-wrapper-fcflags="$(CC_BITS) -L$(MPI_LIBDIR) -R$(MPI_LIBDIR)"
CONFIGURE_OPTIONS += --with-wrapper-libs="$(CC_BITS) -L$(MPI_LIBDIR) -R$(MPI_LIBDIR)"
CONFIGURE_OPTIONS += --without-slurm
CONFIGURE_OPTIONS += ompi_cv_fortran_ignore_tkr_data=0

$(BUILD_DIR)/modulefile.%:		files/modulefile
	/bin/sed -e "s#%%BITS%%#$*#g" \
	-e "s#%%COMPONENT_FMRI%%#$(COMPONENT_FMRI)#g" \
	-e "s#%%COMPONENT_VERSION%%#$(COMPONENT_VERSION)#g" \
	-e "s#%%MODULE_CONFLICTS%%#$(MPI_IMPLEMENTATIONS_LIST)#g" \
	-e "s#%%MODULE_INCDIR%%#$(MPI_INCDIR)#g" \
	-e "s#%%MODULE_PREFIX%%#$(MPI_PREFIX.$*)#g" < $< > $@ ;

PROTO_MODULE_PATH = $(PROTO_DIR)$(MODULE_PATH)/$(COMPONENT_NAME)

install:	$(INSTALL_64) $(BUILD_DIR)/modulefile.64
	$(MKDIR) $(PROTO_MODULE_PATH)/64
	$(CP) $(BUILD_DIR)/modulefile.64 $(PROTO_MODULE_PATH)/64/$(COMPONENT_VERSION)

# Build dependencies
REQUIRED_PACKAGES += system/header/header-picl
REQUIRED_PACKAGES += diagnostic/cpu-counters
REQUIRED_PACKAGES += service/picl

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += developer/hwloc
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += package/environment-modules
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
