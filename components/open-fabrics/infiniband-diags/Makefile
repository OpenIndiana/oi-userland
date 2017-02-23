
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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../ofed-component-macros.mk

COMPONENT_NAME=		infiniband-diags
COMPONENT_VERSION=	1.6.5
COMPONENT_ARCHIVE_HASH=	\
    sha256:53c4ffbc74bec30ea7fdba7bad957b557c6ee6759e337d0a130c1b0817f51307
COMPONENT_ARCHIVE_URL=	https://www.openfabrics.org/downloads/management/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/ofuv_tools
COMPONENT_ANITYA_ID=	1379

INSTALL_TARGET=
include ../ofed-component.mk

CFLAGS += -I$(PROTOUSRINCDIR)/infiniband

LIBS +=	-lopensm -losmvendor -losmcomp -libumad -libmad -libverbs -lglib-2.0

COMPONENT_PREP_ACTION = \
        cp solaris_set_nodedesc.c $(@D)/src

CONFIGURE_ENV += PERL=$(PERL)
COMPONENT_INSTALL_ENV += PERL=$(PERL)

LDFLAGS += -L$(PROTOUSRLIBDIR64)

#
# For some weird reason PKG_CONFIG is generating
# additional linker flags for 64bit builds. We are enforcing
# the GLIB_LIBS with only glib-2.0 here.
#
CONFIGURE_ENV +=       GLIB_LIBS="-lglib-2.0"

CONFIGURE_OPTIONS +=   --sysconfdir=$(ETCDIR)/infiniband
CONFIGURE_OPTIONS +=   --disable-rdma-ndd
CONFIGURE_OPTIONS +=   --enable-compat-utils
CONFIGURE_OPTIONS +=   --enable-test-utils

# it apears that configure is broken
COMPONENT_BUILD_ARGS  +=	LIBS="$(LIBS)"

COMPONENT_PRE_CONFIGURE_ACTION =\
	$(SYMLINK) ../../$(COMPONENT_SRC)/include $(@D)/include

COMPONENT_POST_CONFIGURE_ACTION=\
	$(SYMLINK) ../../../$(COMPONENT_SRC)/scripts/IBswcountlimits.pm $(@D)/scripts

# Adjust '#!/usr/bin/perl'
PERL_SCRIPTS= \
	$(PROTOUSRSBINDIR)/ibdiscover.pl \
	$(PROTOUSRSBINDIR)/ibfindnodesusing.pl \
	$(PROTOUSRSBINDIR)/ibidsverify.pl \
	$(PROTOUSRSBINDIR)/iblinkinfo.pl \
	$(PROTOUSRSBINDIR)/ibprintca.pl \
	$(PROTOUSRSBINDIR)/ibprintrt.pl \
	$(PROTOUSRSBINDIR)/ibprintswitch.pl \
	$(PROTOUSRSBINDIR)/ibqueryerrors.pl \
	$(PROTOUSRSBINDIR)/ibswportwatch.pl

CLEANUP_FILES =\
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/libibnetdisc.la\
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/libibnetdisc.so \
	$(PROTOUSRBINDIR)/vendstat\
	$(PROTOUSRBINDIR)/dump_lfts.sh \
	$(PROTOUSRBINDIR)/dump_mfts.sh\
	$(PROTOUSRBINDIR)/ibidsverify.pl \
	$(PROTOUSRBINDIR)/ibfindnodesusing.pl\
	$(PROTOUSRSHAREMAN8DIR)/vendstat.8 \
	$(PROTOUSRSHAREMAN8DIR)/dump_lfts.8 \
	$(PROTOUSRSHAREMAN8DIR)/dump_mfts.8 \
	$(PROTOUSRSHAREMAN8DIR)/ibidsverify.8 \
	$(PROTOUSRSHAREMAN8DIR)/ibfindnodesusing.8 \
	$(PROTOUSRINCDIR)/infiniband/ibnetdisc.h\

COMPONENT_POST_INSTALL_ACTION+= \
	$(RM) $(CLEANUP_FILES); \
	$(INSTALL) -m 644 manpages/set_nodedesc.sh.8 $(PROTOUSRSHAREMAN8DIR)

# common targets
install:	$(INSTALL_64)

