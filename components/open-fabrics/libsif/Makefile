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
BUILD_BITS= 64
COMPILER= gcc
include ../../../make-rules/shared-macros.mk
include libsif-macros.mk

COMPONENT_NAME=         $(LIBSIF_COMPONENT_NAME)
COMPONENT_VERSION=      $(LIBSIF_COMPONENT_VERSION)
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:ffa472db19614ff27988875ed474e6dcd233273c14dec3ad589ff149288d44b3
COMPONENT_SERVER=       download.oracle.com
COMPONENT_ARCHIVE_URL=	http://$(COMPONENT_SERVER)/otn-pub/oss/networking/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/ofuv_psif

include ../ofed-component.mk

REMOVE_OLD_SRC= sif.h sif_user.h sif_int_user.h os_header.h psif_api.h psif_endian.h psif_hw_print.c psif_hw_print.h psif_hw_data* \
	       	psif_hw_setget* psif_hw_macro* kernel_types.h
# --disable-libcheck is not a supported option for this component
DISABLE_LIBCHECK=

LIBS +=	-libverbs
LDFLAGS +=	-L$(PROTO_DIR)/$(CONFIGURE_LIBDIR.$(BITS))

CPPFLAGS += -DSOLARIS -I../../include/sif/ -I../../include/psifapi/ -I../../$(COMPONENT_SRC)/src/

CONFIGURE_OPTIONS +=   --sysconfdir=$(ETCDIR)/infiniband

COMPONENT_PREP_ACTION += cd $(COMPONENT_SRC)/src/ ; rm $(REMOVE_OLD_SRC) ; cd - ; \
                (cd $(@D); \
		autoreconf -ivf ; \
		aclocal --force ; \
		libtoolize --copy --force --ltdl ; \
		autoconf --force ; \
		autoheader --force)

COMPONENT_POST_INSTALL_ACTION =\
	$(RM) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/$(COMPONENT_NAME).la;\
	$(RM) $(PROTO_DIR)/$(CONFIGURE_LIBDIR.64)/$(COMPONENT_NAME).la;
