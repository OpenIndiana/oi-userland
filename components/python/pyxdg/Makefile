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
# Copyright (c) 2014 Alexander Pyhalov.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pyxdg
COMPONENT_VERSION=	0.25
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://freedesktop.org/wiki/Software/pyxdg/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:81e883e0b9517d624e8b0499eb267b82a815c0b7146d5269f364988ae031279d
COMPONENT_ARCHIVE_URL=	http://people.freedesktop.org/~takluyver/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += runtime/python-27
