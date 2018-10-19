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
# Copyright 2018 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zc.lockfile
COMPONENT_VERSION=	1.3.0
COMPONENT_SUMMARY=	'Portable inter-process lock implementation'
COMPONENT_PROJECT_URL=	https://pypi.org/project/zc.lockfile/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:96cb13769e042988ea25d23d44cf09342ea0f887083d0f9736968f3617665853
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/zc.lockfile
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	ZPL2.1
COMPONENT_LICENSE_FILE=	LICENSE.txt

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:           $(NO_TEST)
