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

ifeq ($(strip $(PYTHON_BOOTSTRAP)),yes)
# To bootstrap the bootstrapper we need to make sure it finds its own modules
ifeq ($(strip $(COMPONENT_NAME)),pyproject_installer)
PYTHON_ENV += PYTHONPATH=$(@D)/src
endif

COMPONENT_BUILD_CMD =		$(PYTHON) -m pyproject_installer build
COMPONENT_BUILD_ARGS =

COMPONENT_INSTALL_CMD =		$(PYTHON) -m pyproject_installer install
COMPONENT_INSTALL_ARGS =
COMPONENT_INSTALL_ARGS +=	--destdir $(PROTO_DIR)

# pyproject_installer does not bytecompile after the install.  Since we need
# pyc files we need to force that.
COMPONENT_POST_INSTALL_ACTION += \
	$(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_DIR)/site-packages $(PROTO_DIR)/$(PYTHON_LIB) ;
else
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

# Add build dependencies from project metadata to REQUIRED_PACKAGES
REQUIRED_PACKAGES_RESOLVED += $(BUILD_DIR)/META.depend.res
$(BUILD_DIR)/META.depend.res: $(SOURCE_DIR)/.prep
	$(MKDIR) $(BUILD_DIR)
	# PYTHON_ENV is needed four times here to have the PYTHONPATH set
	# properly when we bootstrap the pyproject_installer bootstrapper.
	$(PYTHON_ENV) $(PYTHON) -m pyproject_installer deps --depsconfig $(BUILD_DIR)/pyproject_deps.json add build_pep517 pep517
	$(PYTHON_ENV) $(PYTHON) -m pyproject_installer deps --depsconfig $(BUILD_DIR)/pyproject_deps.json add build_pep518 pep518
	cd $(SOURCE_DIR) ; $(PYTHON_ENV) $(PYTHON) -m pyproject_installer deps --depsconfig $(BUILD_DIR)/pyproject_deps.json sync
	$(PYTHON_ENV) $(PYTHON) -m pyproject_installer deps --depsconfig $(BUILD_DIR)/pyproject_deps.json eval --depformat '$$nname' \
		| $(GSED) -e 's/.*/depend type=require fmri=pkg:\/library\/python\/&-$$(PYV)/' \
		> $@

# We need pyproject_installer for two purposes:
# - to detect build dependencies for all Python projects, and
# - to bootstrap some other Python projects.
# The pyproject_installer is not needed (and cannot be needed) for its own
# build.
ifneq ($(strip $(COMPONENT_NAME)),pyproject_installer)
PYTHON_USERLAND_REQUIRED_PACKAGES += library/python/pyproject-installer
endif
