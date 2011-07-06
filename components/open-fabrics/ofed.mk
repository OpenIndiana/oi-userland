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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

# Since we are building these as a set and not packaging them individually at
# this time, each OFED component should install in a common prototype directory
# so we override PROTO_DIR
PROTO_DIR = $(WS_COMPONENTS)/open-fabrics/prototype/$(MACH)

# OFED only builds with GCC
COMPILER=gcc

CPPFLAGS += "-Wformat=2"
CFLAGS += -D_REENTRANT

# Since we are not currently packaging the various OFED components separately
# and we still need headers and to link with the components that we are
# building, we need to point the compiler and linker at a common proto area
# for OFED component headers and libraries.
SHARED_INCLUDES += -I$(PROTO_DIR)/usr/include

# We need to insert the shared "proto" area include directories at the front
# of any compile line to preempt the system headers.  It seems that the "best"
# way to do this is to augment the C/C++ compiler macros. YUCK!!!!
CC += $(SHARED_INCLUDES)
CXX += $(SHARED_INCLUDES)


# This is generally required, but must be overridable
DISABLE_LIBCHECK =	--disable-libcheck

CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"
CONFIGURE_ENV +=	LD_OPTIONS="-R$(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS))"

COMPONENT_INSTALL_ENV +=	LDFLAGS="-L$(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS))"

COMPONENT_BUILD_ENV +=	CPPFLAGS="$(CPPFLAGS)"
COMPONENT_BUILD_ENV +=	LIBS="$(LIBS)"
COMPONENT_BUILD_ENV +=	LDFLAGS="-L$(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS)) $(LIBS)"

COMPONENT_BUILD_ARGS +=	LDFLAGS="-L$(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS)) $(LIBS)"

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	$(DISABLE_LIBCHECK)

CLEAN_PATHS += $(BUILD_DIR)
