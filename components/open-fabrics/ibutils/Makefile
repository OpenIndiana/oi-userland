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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		ibutils
COMPONENT_VERSION=	1.5.7
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8db2fcb20102c37e7037826c58b899092df034aac870d3d50a13263746f17f18
COMPONENT_ARCHIVE_URL=	http://www.openfabrics.org/downloads/ibutils/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include ../ofed.mk

LIBS +=	-lsocket -lnsl -lopensm -losmvendor -losmcomp -libumad -libmad

# we want to use the libcheck here
DISABLE_LIBCHECK=

CONFIGURE_ENV +=	INSTALL_DATA="$(INSTALL) -m 644"

CONFIGURE_OPTIONS +=	--with-osm=$(PROTO_DIR)/usr

PROTOMAN =	$(PROTO_DIR)/$(CONFIGURE_MANDIR)

CLEANUP_FILES =\
	$(PROTOUSRLIBDIR)/libibdm.la\
	$(PROTOUSRLIBDIR)/libibdmcom.la\
	$(PROTOUSRLIBDIR)/libibdm.a\
	$(PROTOUSRLIBDIR)/libibdm.so\
	$(PROTOUSRLIBDIR)/libibdm.so.1 \
	$(PROTOUSRLIBDIR)/libibdmcom.a\
	$(PROTOUSRLIBDIR)/libibdm.so.1.1.1 \
	$(PROTOUSRLIBDIR)/libibdmcom.so\
	$(PROTOUSRLIBDIR)/libibdmcom.so.1 \
	$(PROTOUSRLIBDIR)/libibdmcom.so.1.1.1\
	$(PROTOUSRLIBDIR)/libibsysapi.a\
	$(PROTOUSRLIBDIR)/libibsysapi.la \
	$(PROTOUSRLIBDIR)/libibsysapi.so\
	$(PROTOUSRLIBDIR)/libibsysapi.so.1 \
	$(PROTOUSRLIBDIR)/libibsysapi.so.1.0.0 \
	$(PROTOUSRBINDIR)/ibtopodiff\
	$(PROTOUSRBINDIR)/git_version.tcl \
	$(PROTOUSRBINDIR)/ibdmsh*\
	$(PROTOUSRBINDIR)/ibdmtr* \
	$(PROTOUSRBINDIR)/ibdmchk*\
	$(PROTOUSRBINDIR)/ibdiagui* \
	$(PROTOUSRBINDIR)/ibnlparse*\
	$(PROTOUSRBINDIR)/ibdiagpath* \
	$(PROTOMAN)/man1//ibdmsh.1 \
	$(PROTOMAN)/man1//ibdmtr.1\
	$(PROTOMAN)/man1//ibdmchk.1\
	$(PROTOMAN)/man1//ibdiagui.1 \
	$(PROTOMAN)/man1//ibdiagpath.1\
	$(PROTOMAN)/man1//ibtopodiff.1 \
	$(PROTOMAN)/man1//ibdm-ibnl-file.1\
	$(PROTOMAN)/man1//ibdm-topo-file.1 \
	$(PROTOMAN)/man3//ibnd_discover_fabric.3\
	$(PROTOMAN)/man3//ibnd_find_node_dr.3 \
	$(PROTOMAN)/man3//ibnd_find_node_guid.3\
	$(PROTOMAN)/man3//ibnd_iter_nodes.3 \
	$(PROTOMAN)/man3//ibnd_iter_nodes_type.3\
	$(PROTOMAN)/man3//ibnd_show_progress.3 \

CLEANUP_DIRS=\
	$(PROTOUSRINCDIR)/ibdm\
	$(PROTOUSRLIBDIR)/ibdiagui1.*\
	$(PROTOUSRLIBDIR)/ibdiagpath1.*

COMPONENT_POST_INSTALL_ACTION=\
	$(RM) $(CLEANUP_FILES);\
	$(RM) -r $(CLEANUP_DIRS)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
