
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

# OFED only builds with GCC
COMPILER=gcc

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		infiniband-diags
COMPONENT_VERSION=	1.5.8
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0baf6694d54602a66dfc2b82a765c933b24534fd8e2bda7e9b89abf503b29c02
COMPONENT_ARCHIVE_URL=	http://www.openfabrics.org/downloads/management/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/ofuv_tools

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include ../ofed.mk

MAN8FILES = set_nodedesc.sh.8

CFLAGS += -I$(PROTO_DIR)/usr/include/infiniband
LIBS +=	-lsocket -lnsl -lopensm -losmvendor -losmcomp -libumad -libmad -libverbs -ldevinfo

COMPONENT_PREP_ACTION = \
        cp solaris_set_nodedesc.c $(@D)/src

COMPONENT_INSTALL_ENV +=	PERL=$(PERL.5.12)

CONFIGURE_ENV +=	PERL=$(PERL.5.12)

CONFIGURE_OPTIONS +=	--sbindir=$(USRSBINDIR)

# it apears that configure is broken
COMPONENT_BUILD_ARGS  +=	LIBS="$(LIBS)"

COMPONENT_PRE_CONFIGURE_ACTION =\
	$(SYMLINK) ../../$(COMPONENT_SRC)/include $(@D)/include

COMPONENT_POST_CONFIGURE_ACTION=\
	$(SYMLINK) ../../../$(COMPONENT_SRC)/scripts/IBswcountlimits.pm $(@D)/scripts

PROTOMAN = $(PROTO_DIR)/$(CONFIGURE_MANDIR)

CLEANUP_FILES =\
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/libibnetdisc.la\
	$(PROTO_DIR)/$(CONFIGURE_LIBDIR.32)/libibnetdisc.so \
	$(PROTOUSRBINDIR)/vendstat\
	$(PROTOUSRBINDIR)/dump_lfts.sh \
	$(PROTOUSRBINDIR)/dump_mfts.sh\
	$(PROTOUSRBINDIR)/ibidsverify.pl \
	$(PROTOUSRBINDIR)/ibfindnodesusing.pl\
	$(PROTOMAN)/man8/vendstat.8 \
	$(PROTOMAN)/man8/dump_lfts.8 \
	$(PROTOMAN)/man8/dump_mfts.8 \
	$(PROTOMAN)/man8/ibidsverify.8 \
	$(PROTOMAN)/man8/ibfindnodesusing.8 \
	$(PROTOUSRINCDIR)/infiniband/ibnetdisc.h\

COMPONENT_POST_INSTALL_ACTION =\
	$(RM) $(CLEANUP_FILES);\
	$(INSTALL) -m 644 manpages/set_nodedesc.sh.8 $(PROTOMAN)/man8

# common targets
configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64) #$(PROTOMAN8FILES)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)
