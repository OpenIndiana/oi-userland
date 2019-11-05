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
# Copyright (c) 2011, 2018, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gutenprint
COMPONENT_VERSION=	5.2.14
COMPONENT_SUMMARY=  Gutenprint - Drivers for Canon, Epson, Lexmark & PCL printers
COMPONENT_PROJECT_URL=	http://www.gutenprint.org/software/gutenprint/
COMPONENT_FMRI=     print/filter/gutenprint
COMPONENT_CLASSIFICATION=System/Printing
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
  sha256:45bf0766f196a764c113bfad7ab1ea748f1d5ff9ebb0d3a2206705fe52e82389
COMPONENT_ARCHIVE_URL= \
  http://downloads.sourceforge.net/project/gimp-print/gutenprint-5.2/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=  GPLv2, FDLv1.2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += --enable-escputil
CONFIGURE_OPTIONS += --without-gimp2
CONFIGURE_OPTIONS += --enable-cups-1_2-enhancements
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static-genppd
CONFIGURE_OPTIONS += --enable-simplified-cups-ppds
CONFIGURE_OPTIONS += --without-readline
CONFIGURE_OPTIONS += --disable-static

COMPONENT_BUILD_TARGETS = all

# Needed for "gmake test" to work successfully.  If SHELLOPTS is exported (as
# it is by the Userland Makefiles), then all shell options get exported to
# child invocations of bash, which results in test failures due to nounset and
# xtrace being set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

build:		$(BUILD_32)

install:	$(INSTALL_32)

# the tests mostly pass, but it can't find several drivers for ppd files
test:		$(TEST_32)

# Sustaining dependencies
REQUIRED_PACKAGES += runtime/perl-522

# Auto-generated dependencies
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libusb-1
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
