#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2016 Sergey Avseyev
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		arpack
COMPONENT_VERSION=	3.6.3
COMPONENT_REVISION=	1
REAL_NAME=		arpack-ng
COMPONENT_PROJECT_URL=	https://github.com/opencollab/arpack-ng
COMPONENT_SUMMARY=	Collection of Fortran77 subroutines designed to solve large scale eigenvalue problems
COMPONENT_DESCRIPTION=	The package is designed to compute a few eigenvalues and corresponding eigenvectors of a general n by n matrix A. It is most appropriate for large sparse or structured matrices A where structured means that a matrix-vector product w <- Av requires order n rather than the usual order n**2 floating point operations. This software is based upon an algorithmic variant of the Arnoldi process called the Implicitly Restarted Arnoldi Method (IRAM).
COMPONENT_FMRI=         library/math/arpack
COMPONENT_CLASSIFICATION=       System/Libraries
COMPONENT_SRC=		$(REAL_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:64f3551e5a2f8497399d82af3076b6a33bf1bc95fc46bbcabe66442db366f453
COMPONENT_ARCHIVE_URL= \
  https://github.com/opencollab/$(REAL_NAME)/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf --force --install && libtoolize --force --copy )

CONFIGURE_OPTIONS += --disable-dependency-tracking

COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset set unexpectedly,
# and errors such as "libtool_install_magic: unbound variable"
unexport SHELLOPTS

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/math/openblas
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GFORTRAN_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
