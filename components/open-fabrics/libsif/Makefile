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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
COMPILER = gcc
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsif
COMPONENT_VERSION=	1.0
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:501858b4b9d45ebe163d9136f7fb4d08708aaf91cc97c40059ae2a1b4737239d
COMPONENT_SERVER=      download.oracle.com
COMPONENT_ARCHIVE_URL= http://$(COMPONENT_SERVER)/otn-pub/oss/networking/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/ofuv_psif

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include ../ofed.mk

REMOVE_OLD_SRC= sif.h sif_user.h sif_int_user.h os_header.h psif_api.h psif_endian.h psif_hw_print.h psif_hw_data* psif_hw_setget* psif_hw_macro* kernel_types.h
# --disable-libcheck is not a supported option for this component
DISABLE_LIBCHECK=

LIBS +=	-libverbs
LDFLAGS +=	-L$(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS))

CONFIGURE_ENV += CPPFLAGS=" -DSOLARIS $(CPPFLAGS) -I../../include/sif/ -I../../include/psifapi/ -I../../$(COMPONENT_SRC)/src/ "

CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"

COMPONENT_PREP_ACTION += cd $(COMPONENT_SRC)/src/ ; rm $(REMOVE_OLD_SRC) ; cd - ; \
                (cd $(@D); \
		autoreconf -ivf ; \
		aclocal --force ; \
		libtoolize --copy --force --ltdl ; \
		autoconf --force ; \
		autoheader --force)

COMPONENT_POST_INSTALL_ACTION =\
	$(RM) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/$(COMPONENT_NAME).la;\
	$(RM) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/$(COMPONENT_NAME).la;\

# common targets
configure:	$(CONFIGURE_64)

build_sparc:	$(BUILD_64)

build_i386:
		@echo "Not available."

build:		build_$(MACH)

install_sparc:	$(INSTALL_64)

install_i386:
		@echo "Not available."

install:	install_$(MACH)

# we're sparc-only
ifeq ($(MACH), i386)
PUBLISH_STAMP=
endif

test:		$(NO_TESTS)

system-test:	$(NO_TESTS)
