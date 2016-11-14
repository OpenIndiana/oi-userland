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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS=		64
# For now, all things built for C++11 require gcc.
COMPILER =		gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		espeak
COMPONENT_VERSION=	1.44.05
IPS_COMPONENT_VERSION=	1.44.0.5
COMPONENT_PROJECT_URL=	http://espeak.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)-source
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).zip
COMPONENT_ARCHIVE_HASH= \
	sha256:89c37e69a7348d638c859ea492958145a790d0d57a057b29f2f5d913541f8ef9
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/espeak/files/$(COMPONENT_NAME)/$(COMPONENT_NAME)-$(basename $(COMPONENT_VERSION))/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/accessibility

TPNO=	 		7478

BUILD_STYLE = justmake
TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION += ($(CLONEY) $(SOURCE_DIR) $(@D)) ;

CPPFLAGS.sparc += -DBYTE_ORDER=BIG_ENDIAN
CPPFLAGS += $(CPPFLAGS.$(MACH))

# wave_sada.cpp won't build without -fpermissive
CXXFLAGS += -fpermissive

COMPONENT_BUILD_ARGS += AUDIO="sada"
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CFLAGS="$(CPPFLAGS) $(CFLAGS)"
COMPONENT_BUILD_ARGS += CXX="$(CXX)"
COMPONENT_BUILD_ARGS += CXXFLAGS="$(CPPFLAGS) $(CXXFLAGS)"
COMPONENT_BUILD_ARGS += EXTRA_LIBS="-lm"

COMPONENT_PRE_BUILD_ACTION.sparc += \
	(cd $(@D)/platforms/big_endian ; $(ENV) $(COMPONENT_BUILD_ENV) \
	 $(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS) ; \
	 ./espeak-phoneme-data $(SOURCE_DIR)/espeak-data ../../espeak-data ) ;
COMPONENT_PRE_BUILD_ACTION += $(COMPONENT_PRE_BUILD_ACTION.$(MACH))

# Need to override defaults from justmake.mk to cd into src subdirectory
COMPONENT_BUILD_ACTION = \
	cd $(@D)/src; $(ENV) $(COMPONENT_BUILD_ENV) \
	 $(GMAKE) $(COMPONENT_BUILD_ARGS) $(COMPONENT_BUILD_TARGETS)
COMPONENT_INSTALL_ACTION = \
	cd $(@D)/src ; $(ENV) $(COMPONENT_INSTALL_ENV) \
	 $(GMAKE) $(COMPONENT_INSTALL_ARGS) $(COMPONENT_INSTALL_TARGETS)

COMPONENT_INSTALL_ARGS += $(COMPONENT_BUILD_ARGS)
COMPONENT_INSTALL_ARGS += LIBDIR=$(USRLIB)

REQUIRED_PACKAGES += system/library/math
