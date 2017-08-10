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
COMPONENT_VERSION=	8.6.7
COMPONENT_MINOR_VERSION=	$(shell echo $(COMPONENT_VERSION) | $(GSED) -e 's/\([0-9]\+\)\.\([0-9]\+\)\.[0-9]\+/\1.\2/')
COMPONENT_PROJECT_URL=	http://prdownloads.sourceforge.net/tk/
COMPONENT_SRC=		$(COMPONENT_NAME)$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:061de2a354f9b7c7d04de3984c90c9bc6dd3a1b8377bb45509f1ad8a8d6337aa
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/tcl/files/Tcl/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	library/libtk
COMPONENT_LICENSE=	BSD-like
COMPONENT_LICENSE_FILE=	license.terms

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = \
	(cd $(@D)/unix ; autoreconf -f)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

#This macro will help to look for the configure
#file at the pointed location
CONFIGURE_SCRIPT = $(SOURCE_DIR)/unix/configure

CONFIGURE_BINDIR.32 =  $(CONFIGURE_PREFIX)/bin/$(MACH32)

CFLAGS += $(XPG6MODE) -std=c99

CONFIGURE_OPTIONS	+= --enable-shared
CONFIGURE_OPTIONS	+= --enable-man-symlinks
CONFIGURE_OPTIONS	+= --enable-threads
CONFIGURE_OPTIONS	+= --with-tcl="$(COMPONENT_DIR)/../tcl/build/$(MACH$(BITS))"
# Prevents a '64-bit runpath in 32-bit binary' pkglint warning:
CONFIGURE_OPTIONS.32	+= -x-libraries=/usr/lib
CONFIGURE_OPTIONS.64	+= --enable-64bit

COMPONENT_TEST_ENV =		DISPLAY=:1
COMPONENT_TEST_TARGETS =	test

# Tests are run using an X virtual framebuffer.
# When we have the equivalent of REQUIRED_PACKAGES for test dependencies,
# then we will need to make sure that x11/server/xvfb is included in that list.

COMPONENT_PRE_TEST_ACTION = \
	$(SHELL) $(COMPONENT_DIR)/start_Xvfb $(COMPONENT_DIR)
COMPONENT_POST_TEST_ACTION = \
	$(SHELL) $(COMPONENT_DIR)/stop_Xvfb $(COMPONENT_DIR)

# Test results differ between 32-bit and 64-bit and x86 and SPARC.
COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-$(BITS)-$(MACH).master

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^.*$(CC).*$$|XXX_CC_XXX|"' \
	'-e "s|^.*tcl/build/$(MACH$(BITS)).*$$|XXX_CC_XXX|g"' \
	'-e "s|^cc: Warning: -xarch=v9 is deprecated.*$$|XXX_CC_XXX|g"' \
	'-e "s|^cc: Warning: illegal use of -x.* option, .*$$|XXX_CC_XXX|g"' \
	'-e "/Nothing to be done/d"' \
	'-e "/Leaving directory/d"' \
	'-e "/Entering directory/d"' \
	'-e "/is deprecated/d"' \
	'-e "/tk.*Init.o/d"' \
	'-e "/^XXX_CC_XXX$$/d"' \
	'-e "/^make.*$$/d"' \
	'-e "/^rm .*$$/d"' \
	'-e "/^mv .*$$/d"' \
	'-e "/^Tests began at .*$$/d"' \
	'-e "/^Tests ended at .*$$/d"'

COMPONENT_POST_INSTALL_ACTION += \
	sed -f $(COMPONENT_DIR)/files/tksed.$(BITS) \
		$(PROTO_DIR)$(USRLIBDIR.$(BITS))/tkConfig.sh > \
		$(PROTO_DIR)$(USRLIBDIR.$(BITS))/tkConfig.sh.new; \
	$(MV) $(PROTO_DIR)$(USRLIBDIR.$(BITS))/tkConfig.sh.new \
		$(PROTO_DIR)$(USRLIBDIR.$(BITS))/tkConfig.sh; \
	$(CHMOD) 555 $(PROTO_DIR)$(USRLIBDIR.$(BITS))/tkConfig.sh


# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test: 		$(TEST_32_and_64)

# special targets due to tcl internals dependencies
../tcl/build/%/.built:
	(cd ../tcl ; $(GMAKE) build)

$(CONFIGURE_32):	../tcl/build/$(MACH32)/.built
$(CONFIGURE_64):	../tcl/build/$(MACH64)/.built

PKG_MACROS += COMPONENT_MINOR_VERSION=$(COMPONENT_MINOR_VERSION)

REQUIRED_PACKAGES += runtime/tcl-8
REQUIRED_PACKAGES += system/library/fontconfig
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
REQUIRED_PACKAGES += x11/library/libxext
REQUIRED_PACKAGES += x11/library/libxft
REQUIRED_PACKAGES += x11/server/xvfb
