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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		terminator
COMPONENT_VERSION=	1.91
COMPONENT_PROJECT_URL=	http://www.tenshu.net/terminator/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:95f76e3c0253956d19ceab2f8da709a496f1b9cf9b1c5b8d3cd0b6da3cc7be69
COMPONENT_ARCHIVE_URL=	http://launchpad.net/terminator/gtk3/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS=	2.7

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

PYTHON_DATA=/usr

COMPONENT_POST_INSTALL_ACTION += \
        (cd $(PROTO_DIR)/usr/bin && \
	  $(MV) -f terminator terminator-$(PYTHON_VERSION) && \
	  $(MV) -f remotinator remotinator-$(PYTHON_VERSION) \
	)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/psutil-27
REQUIRED_PACKAGES += library/python/pycairo-27
REQUIRED_PACKAGES += library/python/pygobject-3-27
REQUIRED_PACKAGES += library/python/python-dbus-27
REQUIRED_PACKAGES += runtime/python-27
