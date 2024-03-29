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
# Copyright 2019 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         crmsh
COMPONENT_VERSION=      4.1.0
COMPONENT_REVISION=     2
COMPONENT_FMRI=         application/cluster/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=System/Shells
COMPONENT_PROJECT_URL=  https://github.com/ClusterLabs/crmsh
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:cccd51eb05a121e2b8d66e425057be0b022fa59d187978568411ff4164bf2d03
COMPONENT_ARCHIVE_URL=  https://github.com/ClusterLabs/$(COMPONENT_NAME)/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=      GPLv2
COMPONENT_SUMMARY=      crmsh is a command-line interface for High-Availability cluster management and part of the Clusterlabs project.

include $(WS_MAKE_RULES)/common.mk

ENV += am_cv_python_pythondir=$(PYTHON_VENDOR_PACKAGES)
ENV += am_cv_python_pyexecdir=$(PYTHON_VENDOR_PACKAGES)
ENV += PYTHON_SITELIB=$(PYTHON_VENDOR_PACKAGES)
ENV += PYTHON=$(PYTHON)

COMPONENT_PREP_ACTION=(cd $(SOURCE_DIR); PATH=$(PATH) $(CONFIG_SHELL) autogen.sh )

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_SCRIPT= $(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_PREFIX)/lib
CONFIGURE_OPTIONS += --sharedstatedir=/var/hacluster
CONFIGURE_OPTIONS += --localstatedir=/var

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/lxml
PYTHON_REQUIRED_PACKAGES += runtime/python
