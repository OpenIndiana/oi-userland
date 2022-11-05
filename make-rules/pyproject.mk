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

ifeq ($(strip $(PYTHON_BOOTSTRAP)),yes)
#
# Both 'build' and 'installer' Python modules used for packaging regular Python
# projects (see below) are not part of core Python, so we need to bootstrap
# them together with their non-core dependencies.
#
# There are basically two ways how to bootstrap such projects:
#
# 1) defer to default 'setup.py' build style for projects that still supports
# it.  The 'setup.py' build style usually does not require anything outside
# core Python modules.  Also, it is likely that the set of projects that needs
# to be bootstrapped (like setuptools) will support the 'setup.py' build style
# for very long time (maybe forever).  Anyway, the main problem with the
# 'setup.py' build style is that its results are not PEP 376 compliant.
#
# 2) use something else, preferably as simple as possible, to do the build.
# Such tool needs to be PEP 376 and PEP 517 compliant and it also must be able
# to build itself without requiring any other non-core Python modules.  We use
# pyproject_installer to do the job.
#

ifeq ($(strip $(COMPONENT_NAME)),pyproject_installer)
# To bootstrap the bootstrapper we need to make sure it finds its own modules
PYTHON_ENV += PYTHONPATH=$(@D)/src
endif

# Since pyproject_installer requires Python >= 3.8 we need to defer to default
# setup.py build style for Python 3.7, so we will use pyproject_installer for
# Python 3.9 only.  Once we obsolete Python 3.7 we should set
# COMPONENT_BUILD_CMD, COMPONENT_BUILD_ARGS, COMPONENT_INSTALL_CMD, and
# COMPONENT_INSTALL_ARGS unconditionally below and replace $(PYTHON.3.9) by
# $(PYTHON).
$(BUILD_DIR)/%-3.9/.built:	COMPONENT_BUILD_CMD =		$(PYTHON.3.9) -m pyproject_installer build
$(BUILD_DIR)/%-3.9/.built:	COMPONENT_BUILD_ARGS =

$(BUILD_DIR)/%-3.9/.installed:	COMPONENT_INSTALL_CMD =		$(PYTHON.3.9) -m pyproject_installer install
$(BUILD_DIR)/%-3.9/.installed:	COMPONENT_INSTALL_ARGS =
$(BUILD_DIR)/%-3.9/.installed:	COMPONENT_INSTALL_ARGS +=	--destdir $(PROTO_DIR)

# pyproject_installer does not bytecompile after the install.  Since we need
# pyc files we need to force that.
#
# Since pyproject_installer requires Python >= 3.8 we need to defer to default
# setup.py build style for Python 3.7, and so we do not need to compile for
# Python 3.7.  Once we obsolete Python 3.7 we should set
# COMPONENT_POST_INSTALL_ACTION unconditionally below.
$(BUILD_DIR)/%-3.9/.installed:	COMPONENT_POST_INSTALL_ACTION +=	$(PYTHON) -m compileall $(PROTO_DIR)/$(PYTHON_LIB) ;

# Special transforms needed only until we drop support for Python 3.7
PUBLISH_TRANSFORMS +=	$(WS_TOP)/transforms/python-bootstrap

# We need pyproject_installer to bootstrap other projects, but it is not needed
# (and cannot be needed) for its own bootstrap.
ifneq ($(strip $(COMPONENT_NAME)),pyproject_installer)
# Once we obsolete Python 3.7 this should be changed to
# PYTHON_USERLAND_REQUIRED_PACKAGES and '-39' suffix should be removed
USERLAND_REQUIRED_PACKAGES += library/python/pyproject_installer-39
endif
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
