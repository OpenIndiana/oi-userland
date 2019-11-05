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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	diveintopython
COMPONENT_VERSION= 	5.4
COMPONENT_REVISION=	1
COMPONENT_SUMMARY= 	A book on Python programming
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_NAME)-html-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= \
  sha256:cf51555500b77c51f6a35c59eaf049b23c8729ef3bef31fc445b6aea45d150a6
COMPONENT_ARCHIVE_URL= \
  http://www.diveintopython.net/download/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://www.diveintopython.net/
COMPONENT_LICENSE=	FDLv1.1
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_FMRI=	documentation/diveintopython

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION =        ( cp $(COMPONENT_DIR)/files/Makefile $(@D))

build: $(BUILD_32)

install: $(INSTALL_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/theme/nimbus
REQUIRED_PACKAGES += library/desktop/libgnome
