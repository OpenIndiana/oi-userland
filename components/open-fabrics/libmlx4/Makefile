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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
include ../ofed-component-macros.mk

COMPONENT_NAME=		libmlx4
COMPONENT_VERSION=	1.0.1
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-1.18.gb810a27.tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ac3aa335d5749a8edc471630b1f5049122c8b7b66bab88c299e255122028e19c
COMPONENT_BUGDB=	library/ofuv_lib

include ../ofed-component.mk

# --disable-libcheck is not a supported option for this component
DISABLE_LIBCHECK=

LIBS=	-libverbs
LDFLAGS +=	-L$(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS))

# requires an older automake to reconfigure
COMPONENT_PREP_ACTION += (if [ x$(MACH) = "xi386" ]; then \
		cp mlx4.driver.i386 $(@D)/mlx4.driver; \
		else \
		cp mlx4.driver.sparc $(@D)/mlx4.driver; \
		fi; \
		cd $(@D) ; \
		aclocal-1.11 --force ; \
		libtoolize --copy --force --ltdl ; \
		autoconf --force ; \
		autoheader --force)

COMPONENT_POST_INSTALL_ACTION =\
	$(RM) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/$(COMPONENT_NAME).la;\
	$(RM) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/$(COMPONENT_NAME).la;\

