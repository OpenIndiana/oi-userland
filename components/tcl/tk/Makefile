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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2020, Michal Nowak
# Copyright (c) 2023, Klaus Ziegler
#

include ../../../make-rules/shared-macros.mk

USE_COMMON_TEST_MASTER=		yes
COMPONENT_NAME=			tk
COMPONENT_MAJOR_VERSION=	8.6
COMPONENT_VERSION=		$(COMPONENT_MAJOR_VERSION).13
COMPONENT_REVISION=		1
COMPONENT_SUMMARY=		Tk - TCL GUI Toolkit
COMPONENT_DESCRIPTION=	Tk is an open source, cross-platform widget toolkit that provides a library of basic elements for building a graphical user interface
COMPONENT_PROJECT_URL=	https://www.tcl-lang.org/
COMPONENT_SRC=			$(COMPONENT_NAME)$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC)-src.tar.gz
COMPONENT_ARCHIVE_HASH= sha256:2e65fa069a23365440a3c56c556b8673b5e32a283800d8d9b257e3f584ce0675
COMPONENT_ARCHIVE_URL=	https://prdownloads.sourceforge.net/tcl/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			runtime/tk-8
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=		BSD-like
COMPONENT_LICENSE_FILE=	license.terms

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += COMPONENT_MAJOR_VERSION=$(COMPONENT_MAJOR_VERSION)

COMPONENT_PREP_ACTION= \
	(cd $(@D)/unix ; autoreconf -f)

COMPONENT_PRE_CONFIGURE_ACTION= \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# This macro will help to look for the configure
# file at the pointed location
CONFIGURE_SCRIPT= $(SOURCE_DIR)/unix/configure

CFLAGS += $(XPG6MODE) -std=c99

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --enable-man-symlinks
CONFIGURE_OPTIONS += --enable-threads
CONFIGURE_OPTIONS += --with-tcl="$(COMPONENT_DIR)/../tcl/build/$(MACH$(BITS))"
CONFIGURE_OPTIONS += --enable-64bit
ifeq ($(strip $(MACH)),sparc)
CONFIGURE_OPTIONS += --enable-64bit-vis
endif

# Don't use rpath
COMPONENT_POST_INSTALL_ACTION += \
	find $(PROTO_DIR) -name libtk$(COMPONENT_MAJOR_VERSION).so -exec chmod 0755 {} \; ;

COMPONENT_POST_INSTALL_ACTION += \
	sed -f $(COMPONENT_DIR)/files/tksed $(PROTOUSRLIBDIR64)/tkConfig.sh > \
	$(PROTOUSRLIBDIR64)/tkConfig.sh.new \
	$(MV) $(PROTOUSRLIBDIR64)/tkConfig.sh.new $(PROTOUSRLIBDIR64)/tkConfig.sh; \
	$(CHMOD) 555 $(PROTOUSRLIBDIR64)/tkConfig.sh

# Tests are run using an X virtual framebuffer.
# When we have the equivalent of REQUIRED_PACKAGES for test dependencies,
# then we will need to make sure that x11/server/xvfb is included in that list.
COMPONENT_TEST_ENV =		DISPLAY=:1
COMPONENT_TEST_TARGETS =	test

COMPONENT_PRE_TEST_ACTION = \
	$(SHELL) $(COMPONENT_DIR)/start_Xvfb $(COMPONENT_DIR)
COMPONENT_POST_TEST_ACTION = \
	$(SHELL) $(COMPONENT_DIR)/stop_Xvfb $(COMPONENT_DIR)

# Test results differ between 32-bit and 64-bit and x86 and SPARC.
#COMPONENT_TEST_MASTER = \
#	$(COMPONENT_TEST_RESULTS_DIR)/results-$(BITS)-$(MACH).master

COMPONENT_TEST_TRANSFORMS= \
	'-n' \
	'-e "/Total/p"' \
	'-e "/Sourced/p"' \
	'-e "/failing/p"'

# special targets due to tcl internals dependencies
../tcl/build/%/.built:
	(cd ../tcl ; $(GMAKE) build)

$(CONFIGURE_64):	../tcl/build/$(MACH64)/.built

# Required for test suite
REQUIRED_PACKAGES += x11/server/xvfb

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxft
