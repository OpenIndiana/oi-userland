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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= system-config-printer
COMPONENT_VERSION= 1.4.8
COMPONENT_REVISION= 2
IPS_COMPONENT_VERSION= 2.30.0
COMPONENT_SUMMARY= Print Manager for CUPS
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:9f65e96434819bf4170d654ef5caa945699e48f72bf5ae8c500341409c3db2f9
COMPONENT_ARCHIVE_URL= \
  http://cyberelk.net/tim/data/$(COMPONENT_NAME)/1.4/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL = http://cyberelk.net/tim/software/system-config-printer/

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CFLAGS += -I/usr/X11/include

COMPONENT_PRE_CONFIGURE_ACTION =	(chmod -R u+r  $(SOURCE_DIR) && \
					cp -r $(SOURCE_DIR)/* $(@D))

CONFIGURE_SCRIPT = $(@D)/configure

CONFIGURE_OPTIONS += --sysconfdir=/etc

CONFIGURE_ENV	+= PYTHON=$(PYTHON)

build: $(BUILD_32)

install: $(INSTALL_32)

test: $(NO_TESTS)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/python/pycups-27
REQUIRED_PACKAGES += library/python/pygobject-3-27
REQUIRED_PACKAGES += library/python/python-dbus-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += text/xmlto
