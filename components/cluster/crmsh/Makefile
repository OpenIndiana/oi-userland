#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Adam Stevko. All rights reserved.
# Copyright 2016 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= crmsh
COMPONENT_VERSION= 3.0.3
COMPONENT_FMRI= application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Shells
COMPONENT_PROJECT_URL= https://github.com/ClusterLabs/crmsh
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:364fadb0d0c9619676e10bb75f4ea833a49019aa77ddb26229bc9d1c435585c0
COMPONENT_ARCHIVE_URL=  https://github.com/ClusterLabs/$(COMPONENT_NAME)/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE= GPLv2
COMPONENT_SUMMARY= crmsh is a command-line interface for High-Availability cluster management and part of the Clusterlabs project.


include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
ENV += PYTHON_SITELIB=$(PYTHON_VENDOR_PACKAGES)
ENV += PYTHON=$(PYTHON)

COMPONENT_PREP_ACTION=(cd $(SOURCE_DIR); $(CONFIG_SHELL) autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT= $(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS += --sharedstatedir=/var/hacluster
CONFIGURE_OPTIONS += --localstatedir=/var


build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TESTS_32)

REQUIRED_PACKAGES += runtime/python-27
