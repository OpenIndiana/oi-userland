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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		smp_utils
COMPONENT_VERSION=	0.97
COMPONENT_PROJECT_URL= http://sg.danny.cz/sg/smp_utils.html
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
    sha256:0e10d304cfa8789bcf16537e8f72d9afdf8838fca20ae68103c317432d00915b
COMPONENT_ARCHIVE_URL=	http://sg.danny.cz/sg/p/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/smputils
COMPONENT_ANITYA_ID=	4840

TPNO=			11065

# Needs header file from ON only available in S12.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_64=
INSTALL_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

CPPFLAGS += -I$(COMPONENT_DIR)/$(COMPONENT_SRC)/include
CONFIGURE_OPTIONS +=	--disable-static

# Don't use rpath!
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(BUILD_DIR_64) ; \
	$(GSED) -i 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' libtool ; \
	$(GSED) -i 's|^runpath_var=LD_RUN_PATH|runpath_var=DIE_RPATH_DIE|g' libtool)

COMPONENT_INSTALL_ARGS += INSTALL=$(INSTALL)
COMPONENT_INSTALL_ARGS += INSTALL_TOP=$(PROTOUSRDIR) 
$(INSTALL_64):  COMPONENT_INSTALL_ARGS += INSTALL_LIB=$(PROTOUSRLIBDIR64)
$(INSTALL_64):  COMPONENT_INSTALL_ARGS += INSTALL_SBIN=$(PROTOUSRBINDIR)

COMPONENT_TEST_ENV +=	LD_LIBRARY_PATH=$(PROTOUSRLIBDIR64)
COMPONENT_TEST_CMD =	\
		$(PROTOUSRBINDIR)/smp_conf_general -V; \
		$(PROTOUSRBINDIR)/smp_conf_phy_event -V; \
		$(PROTOUSRBINDIR)/smp_conf_route_info -V; \
		$(PROTOUSRBINDIR)/smp_conf_zone_man_pass -V; \
		$(PROTOUSRBINDIR)/smp_conf_zone_perm_tbl -V; \
		$(PROTOUSRBINDIR)/smp_conf_zone_phy_info -V; \
		$(PROTOUSRBINDIR)/smp_discover -V; \
		$(PROTOUSRBINDIR)/smp_discover_list -V; \
		$(PROTOUSRBINDIR)/smp_ena_dis_zoning -V; \
		$(PROTOUSRBINDIR)/smp_phy_control -V; \
		$(PROTOUSRBINDIR)/smp_phy_test -V; \
		$(PROTOUSRBINDIR)/smp_read_gpio -V; \
		$(PROTOUSRBINDIR)/smp_rep_broadcast -V; \
		$(PROTOUSRBINDIR)/smp_rep_exp_route_tbl -V; \
		$(PROTOUSRBINDIR)/smp_rep_general -V; \
		$(PROTOUSRBINDIR)/smp_rep_manufacturer -V; \
		$(PROTOUSRBINDIR)/smp_rep_phy_err_log -V; \
		$(PROTOUSRBINDIR)/smp_rep_phy_event -V; \
		$(PROTOUSRBINDIR)/smp_rep_phy_event_list -V; \
		$(PROTOUSRBINDIR)/smp_rep_phy_sata -V; \
		$(PROTOUSRBINDIR)/smp_rep_route_info -V; \
		$(PROTOUSRBINDIR)/smp_rep_self_conf_stat -V; \
		$(PROTOUSRBINDIR)/smp_rep_zone_man_pass -V; \
		$(PROTOUSRBINDIR)/smp_rep_zone_perm_tbl -V; \
		$(PROTOUSRBINDIR)/smp_write_gpio -V; \
		$(PROTOUSRBINDIR)/smp_zone_activate -V; \
		$(PROTOUSRBINDIR)/smp_zone_lock -V; \
		$(PROTOUSRBINDIR)/smp_zone_unlock -V; \
		$(PROTOUSRBINDIR)/smp_zoned_broadcast -V

