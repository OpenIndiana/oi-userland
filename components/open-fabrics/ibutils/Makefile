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
include ../ofed-component-macros.mk

COMPONENT_NAME=		ibutils
COMPONENT_VERSION=	1.5.7
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-0.2.gbd7e502.tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:67a3b417c8d0820400045dd7143674824086c6793a40ded333be50e498d9a703
COMPONENT_BUGDB=	utility/ofuv_tools

include ../ofed-component.mk

LIBS +=	-lopensm -losmvendor -losmcomp -libumad -libmad

LDFLAGS += -L$(PROTOUSRLIBDIR64)

# we want to use the libcheck here
DISABLE_LIBCHECK=

CONFIGURE_ENV +=	INSTALL_DATA="$(INSTALL) -m 644"

CONFIGURE_BINDIR.64= $(USRSBINDIR)
CONFIGURE_OPTIONS +=	CXXFLAGS="$(CC_BITS)"
CONFIGURE_OPTIONS +=	--with-osm=$(PROTOUSRDIR)
CONFIGURE_OPTIONS +=	--with-osm-libs=$(PROTOUSRLIBDIR64)

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
	$(PROTOUSRSHAREMAN1DIR)/ibdmsh.1 \
	$(PROTOUSRSHAREMAN1DIR)/ibdmtr.1\
	$(PROTOUSRSHAREMAN1DIR)/ibdmchk.1\
	$(PROTOUSRSHAREMAN1DIR)/ibdiagui.1 \
	$(PROTOUSRSHAREMAN1DIR)/ibdiagpath.1\
	$(PROTOUSRSHAREMAN1DIR)/ibtopodiff.1 \
	$(PROTOUSRSHAREMAN1DIR)/ibdm-ibnl-file.1\
	$(PROTOUSRSHAREMAN1DIR)/ibdm-topo-file.1 \
	$(PROTOUSRSHAREMAN3DIR)/ibnd_discover_fabric.3\
	$(PROTOUSRSHAREMAN3DIR)/ibnd_find_node_dr.3 \
	$(PROTOUSRSHAREMAN3DIR)/ibnd_find_node_guid.3\
	$(PROTOUSRSHAREMAN3DIR)/ibnd_iter_nodes.3 \
	$(PROTOUSRSHAREMAN3DIR)/ibnd_iter_nodes_type.3\
	$(PROTOUSRSHAREMAN3DIR)/ibnd_show_progress.3 \

CLEANUP_DIRS=\
	$(PROTOUSRINCDIR)/ibdm\
	$(PROTOUSRLIBDIR)/ibdiagui1.*\
	$(PROTOUSRLIBDIR)/ibdiagpath1.*

COMPONENT_POST_INSTALL_ACTION=\
	$(RM) $(CLEANUP_FILES);\
	$(RM) -r $(CLEANUP_DIRS)

