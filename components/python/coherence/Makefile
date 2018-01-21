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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		Coherence
COMPONENT_VERSION=	0.6.6.2
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://coherence.beebits.net
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:0b54a6ba88c1ff6274aadb68ff37b8a3961b4c6acf5ded291c5dea936a311ba4
COMPONENT_ARCHIVE_URL=	http://coherence.beebits.net/download/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS=	2.7

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

COMPONENT_POST_INSTALL_ACTION = \
        (cd $(PROTO_DIR) ; \
                $(MV) usr/bin/coherence usr/bin/coherence-$(PYTHON_VERSION); \
		$(GSED) -i -e "s:/usr/bin/env python:$(PYTHON.$(PYTHON_VERSION).32):" usr/lib/python*/vendor-packages/coherence/extern/youtubedl/youtubedl.py )


test:           $(NO_TEST)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/python/configobj-27
REQUIRED_PACKAGES += library/python/python-twisted-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library/dbus
