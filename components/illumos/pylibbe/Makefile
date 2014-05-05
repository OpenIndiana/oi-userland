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
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= pylibbe
COMPONENT_SRC= src

COMPONENT_VERSION= 0.5.11
COMPONENT_SUMMARY= Python library to work with boot environments
COMPONENT_PROJECT_URL = http://www.illumos.org

include $(WS_TOP)/make-rules/justmake.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

download::

clobber: clean

$(SOURCE_DIR)/.prep:
	$(TOUCH) $@

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

clean::
	$(RM) $(SOURCE_DIR)/.prep
