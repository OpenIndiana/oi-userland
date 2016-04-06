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

COMPONENT_NAME=		borgbackup
COMPONENT_VERSION=	1.0.0
COMPONENT_PROJECT_URL=	https://borgbackup.readthedocs.org/en/stable/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:500b9e311331aa88ec07df94d9f3280a79ca207bf1a997b92dd1e6a1f1664671
COMPONENT_ARCHIVE_URL=	https://github.com/borgbackup/borg/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

# Borg requirement
PYTHON_VERSIONS=	3.4

include $(WS_MAKE_RULES)/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_FETCH_USER_AGENT=wget

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:           $(NO_TEST)
