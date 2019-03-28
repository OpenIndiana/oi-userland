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
# Copyright 2019 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		notify2
COMPONENT_VERSION=	0.3.1
COMPONENT_SUMMARY=	'pynotify replacement for differrent GUI toolkits'
COMPONENT_PROJECT_URL=	https://bitbucket.org/takluyver/pynotify2
COMPONENT_FMRI=	library/python/notify2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:33fa108d50c42f3cd3407cc437518ad3f6225d1bb237011f16393c9dd3ce197d
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_LICENSE_FILE = LICENSE
COMPONENT_LICENSE = BSD
COMPONENT_CLASSIFICATION = Development/Python

PYTHON_VERSIONS= 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)
