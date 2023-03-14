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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2018 Michal Nowak
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		system-config-printer
HUMAN_VERSION =			1.5.18
COMPONENT_VERSION =		2.30.0
COMPONENT_REVISION =		7
COMPONENT_FMRI =		print/cups/system-config-printer
COMPONENT_SUMMARY =		Print Manager for CUPS
COMPONENT_CLASSIFICATION =	System/Administration and Configuration
COMPONENT_PROJECT_URL =		https://github.com/OpenPrinting/system-config-printer
COMPONENT_SRC =			$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE =		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH =	sha256:b1a69e1b4ec2add569a87aeca811a37c5361ee6ae327ec852b79e64223e34bee
COMPONENT_ARCHIVE_URL =		$(COMPONENT_PROJECT_URL)/releases/download/v$(HUMAN_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE =		GPL-2.0-only
COMPONENT_LICENSE_FILE =	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_ENV +=	PYTHON=$(PYTHON)
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)

# Fix shebang for Python scripts
PYTHON_SCRIPTS +=	$(USRSHAREDIR)/system-config-printer/applet.py

# Move the applet
COMPONENT_POST_INSTALL_ACTION += \
	$(MKDIR) $(PROTOUSRLIBDIR)/system-config-printer ; \
	$(MV) $(PROTOUSRBINDIR)/system-config-printer-applet $(PROTOUSRLIBDIR)/system-config-printer ; \
	$(GSED) -i -e 's?\/usr\/bin\/python3?\/usr\/bin\/python$(PYTHON_VERSION)?' $(PROTO_DIR)/usr/share/system-config-printer/system-config-printer.py ;

# Remove pyc files we do not want to distribute
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) -r $(PROTOUSRSHAREDIR)/system-config-printer/__pycache__

# Build dependencies
REQUIRED_PACKAGES += text/xmlto

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += library/python/pycups
PYTHON_REQUIRED_PACKAGES += library/python/pygobject-3
PYTHON_REQUIRED_PACKAGES += library/python/python-dbus
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += shell/ksh93
