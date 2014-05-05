#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Aurelien Larcher.  All rights reserved.
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	scientific-py
COMPONENT_VERSION= 	2.8
COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/python-2/scientific-py
COMPONENT_SRC_NAME=	ScientificPython
COMPONENT_SRC= 		$(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL = https://sourcesup.renater.fr/projects/scientific-py/
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:4de6c8d1b28526d0f2db02f30e99a28a8340ee4cc06fa0a5c0d4b20096806908
COMPONENT_ARCHIVE_URL= \
  https://sourcesup.renater.fr/frs/download.php/2309/$(COMPONENT_ARCHIVE)/download
COMPONENT_LICENSE=	CeCILL-C
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license
COMPONENT_SUMMARY= 	Python modules for scientific computing

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL=0

COMPONENT_POST_INSTALL_ACTION+=$(CP) $(PROTO_DIR)/usr/bin/bsp_virtual $(PROTO_DIR)/usr/bin/bsp_virtual$(PYTHON_VERSION);
COMPONENT_POST_INSTALL_ACTION+=$(CP) $(PROTO_DIR)/usr/bin/task_manager $(PROTO_DIR)/usr/bin/task_manager$(PYTHON_VERSION);

$(INSTALL_32):	$(INSTALL_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk

