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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tk
COMPONENT_VERSION=	8.5.12
COMPONENT_PROJECT_URL=	http://prdownloads.sourceforge.net/tk/
COMPONENT_SRC=		$(COMPONENT_NAME)$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c453d820925bf526bbe8a0d1c17ab3168b076fcb9844bea797ad75e3b9ad9291
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/tcl/files/Tcl/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	library/libtk

include ../../../make-rules/prep.mk
include ../../../make-rules/configure.mk
include ../../../make-rules/ips.mk

COMPONENT_PREP_ACTION = \
	(cd $(@D)/unix ; autoreconf -f)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

#This macro will help to look for the configure 
#file at the pointed location 
CONFIGURE_SCRIPT = $(SOURCE_DIR)/unix/configure

CFLAGS += $(XPG6MODE) -std=c99

CONFIGURE_OPTIONS	+= --enable-shared
CONFIGURE_OPTIONS	+= --enable-man-symlinks
CONFIGURE_OPTIONS	+= --enable-threads
CONFIGURE_OPTIONS.32	+= --with-tcl="$(COMPONENT_DIR)/../tcl/build/$(MACH32)"
CONFIGURE_OPTIONS.64	+= --with-tcl="$(COMPONENT_DIR)/../tcl/build/$(MACH64)"
CONFIGURE_OPTIONS.64	+= --enable-64bit

COMPONENT_TEST_TARGETS = test

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64) $(PROTOUSRLIBDIR)/tkConfig.sh 

$(PROTOUSRLIBDIR)/tkConfig.sh:  $(INSTALL_32)  
				sed -f $(COMPONENT_DIR)/files/tksed $(PROTOUSRLIBDIR)/tkConfig.sh > \
					$(PROTOUSRLIBDIR)/tkConfig.sh.new
				$(MV) $(PROTOUSRLIBDIR)/tkConfig.sh.new $(PROTOUSRLIBDIR)/tkConfig.sh
				$(CHMOD) 555 $(PROTOUSRLIBDIR)/tkConfig.sh

test: 		$(TEST_32_and_64)

# special targets due to tcl internals dependencies
../tcl/build/%/.built:
	(cd ../tcl ; $(GMAKE) build)

$(CONFIGURE_32):	../tcl/build/$(MACH32)/.built
$(CONFIGURE_64):	../tcl/build/$(MACH64)/.built

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../../make-rules/depend.mk
