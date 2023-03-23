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

# Since pyproject_installer requires Python >= 3.8 we will use it for Python
# 3.9 only.  Once we obsolete Python 3.7 we should set COMPONENT_BUILD_CMD,
# COMPONENT_BUILD_ARGS, COMPONENT_INSTALL_CMD, and COMPONENT_INSTALL_ARGS
# unconditionally below.
$(BUILD_DIR)/%-3.9/.built:	COMPONENT_BUILD_CMD =		$(PYTHON) -m pyproject_installer build
$(BUILD_DIR)/%-3.9/.built:	COMPONENT_BUILD_ARGS =

$(BUILD_DIR)/%-3.9/.installed:	COMPONENT_INSTALL_CMD =		$(PYTHON) -m pyproject_installer install
$(BUILD_DIR)/%-3.9/.installed:	COMPONENT_INSTALL_ARGS =
$(BUILD_DIR)/%-3.9/.installed:	COMPONENT_INSTALL_ARGS +=	--destdir $(PROTO_DIR)

# pyproject_installer does not bytecompile after the install.  Since we need
# pyc files we need to force that.
#
# Since pyproject_installer requires Python >= 3.8 we do need to compile for
# Python 3.9 only.  Once we obsolete Python 3.7 we should set
# COMPONENT_POST_INSTALL_ACTION unconditionally below.
$(BUILD_DIR)/%-3.9/.installed:	COMPONENT_POST_INSTALL_ACTION += \
	$(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_DIR)/site-packages $(PROTO_DIR)/$(PYTHON_LIB) ;

# Since pyproject_installer requires Python >= 3.8 we cannot use it to
# bootstrap Python 3.7.  We will use 'build' and 'installer' instead.  Strictly
# speaking this is not true bootstrap, but since we do not need to bootstrap
# Python 3.7 from scratch we can afford this fake bootstrap keeping in mind
# that Python 3.7 should be EOLed in June 2023.
$(BUILD_DIR)/%-3.7/.built:	COMPONENT_BUILD_CMD =		$(PYTHON) -m build
$(BUILD_DIR)/%-3.7/.built:	COMPONENT_BUILD_ARGS =
$(BUILD_DIR)/%-3.7/.built:	COMPONENT_BUILD_ARGS +=		--wheel
$(BUILD_DIR)/%-3.7/.built:	COMPONENT_BUILD_ARGS +=		--no-isolation

$(BUILD_DIR)/%-3.7/.installed:	COMPONENT_INSTALL_CMD =		$(PYTHON) -m installer
$(BUILD_DIR)/%-3.7/.installed:	COMPONENT_INSTALL_ARGS =
$(BUILD_DIR)/%-3.7/.installed:	COMPONENT_INSTALL_ARGS +=	--destdir $(PROTO_DIR)
$(BUILD_DIR)/%-3.7/.installed:	COMPONENT_INSTALL_ARGS +=	$(@D)/dist/*.whl

USERLAND_REQUIRED_PACKAGES += library/python/build-37
USERLAND_REQUIRED_PACKAGES += library/python/installer-37

# Remove all files from dist-info directory except METADATA and
# entry_points.txt to get similar layout as with pyproject_installer
$(BUILD_DIR)/%-3.7/.installed:	COMPONENT_POST_INSTALL_ACTION += \
	( cd $(PROTO_DIR)/$(PYTHON_LIB)/$(COMPONENT_NAME)-$(COMPONENT_VERSION).dist-info ; \
	for f in * ; do \
		[[ "$$f" == "METADATA" ]] && continue ; \
		[[ "$$f" == "entry_points.txt" ]] && continue ; \
		[[ -f "$$f" ]] || continue ; \
		$(RM) $$f ; \
	done ) ;
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

# To make the package names comparable we normalize them by following the PyPA
# Core metadata specifications and PEP 503.
#
# Before we reach bootstrap checkpoint 2 we use simple normalizer for build
# dependencies.  After that we use python-requires to get dependencies
# evaluated too.
ifneq ($(filter $(strip $(COMPONENT_NAME)),$(PYTHON_BOOTSTRAP_CHECKPOINT_2)),)
PYTHON_PACKAGE_NORMALIZER = \
	$(GSED) -e $$'s/^[ \t]*''\([a-zA-Z0-9]\([a-zA-Z0-9._-]*[a-zA-Z0-9]\)\{0,1\}\).*/\1/' \
	| tr [A-Z] [a-z] | $(GSED) -e 's/[._-]\{1,\}/-/g'
else
PYTHON_PACKAGE_NORMALIZER = \
	$(PYTHON) $(WS_TOOLS)/python-requires -
endif

# Add build dependencies from project metadata to REQUIRED_PACKAGES
REQUIRED_PACKAGES_RESOLVED += $(BUILD_DIR)/META.depend.res
$(BUILD_DIR)/META.depend.res: $(SOURCE_DIR)/.prep
	$(MKDIR) $(BUILD_DIR)
	# PYTHON_ENV is needed here to have the PYTHONPATH set properly when we
	# bootstrap the pyproject_installer bootstrapper.
	#
	# Once we obsolete Python 3.7 we should change $(PYTHON.3.9) to $(PYTHON) here
	$(PYTHON_ENV) $(PYTHON.3.9) -c ' \
			from pathlib import Path; \
			from pyproject_installer.build_cmd._build import parse_build_system_spec; \
			[print(x) for x in parse_build_system_spec(Path("'$(SOURCE_DIR)'"))["requires"]]' \
		| $(PYTHON_PACKAGE_NORMALIZER) \
		| $(GSED) -e 's/.*/depend type=require fmri=pkg:\/library\/python\/&-$$(PYV)/' \
		> $@

# We need pyproject_installer for two purposes:
# - to detect build dependencies for all Python projects, and
# - to bootstrap some other Python projects.
# The pyproject_installer is not needed (and cannot be needed) for its own
# build.
ifneq ($(strip $(COMPONENT_NAME)),pyproject_installer)
# Once we obsolete Python 3.7 this should be changed to
# PYTHON_USERLAND_REQUIRED_PACKAGES and '-39' suffix should be removed
USERLAND_REQUIRED_PACKAGES += library/python/pyproject-installer-39
endif
