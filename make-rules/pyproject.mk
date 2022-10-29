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
# Copyright 2022 Marcel Telka
#

include $(WS_MAKE_RULES)/setup.py.mk

PYTHON_BOOTSTRAP ?= no

# Both build and installer Python modules together with versioned
# library/python/build and library/python/installer packages are not available
# during bootstrap.
ifeq ($(strip $(PYTHON_BOOTSTRAP)),no)
COMPONENT_BUILD_CMD =		$(PYTHON) -m build
COMPONENT_BUILD_ARGS =
COMPONENT_BUILD_ARGS +=		--wheel
COMPONENT_BUILD_ARGS +=		--no-isolation

COMPONENT_INSTALL_CMD =		$(PYTHON) -m installer
COMPONENT_INSTALL_ARGS =
COMPONENT_INSTALL_ARGS +=	--destdir $(PROTO_DIR)
COMPONENT_INSTALL_ARGS +=	$(@D)/dist/*.whl

PYTHON_USERLAND_REQUIRED_PACKAGES += library/python/build
PYTHON_USERLAND_REQUIRED_PACKAGES += library/python/installer
endif

# Move all modules from default site-packages directory to vendor-packages
# directory where we place modules shipped by the OS but not included in the
# core Python distribution.
COMPONENT_POST_INSTALL_ACTION += \
	if [ -d $(PROTO_DIR)/$(PYTHON_DIR)/site-packages ] ; then \
		$(RM) -r $(PROTO_DIR)/$(PYTHON_LIB) ; \
		$(MV) $(PROTO_DIR)/$(PYTHON_DIR)/site-packages $(PROTO_DIR)/$(PYTHON_LIB) ; \
	fi ;
