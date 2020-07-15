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
# Copyright (c) 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		typing
COMPONENT_VERSION=	3.6.2
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/typing
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d514bd84b284dd3e844f0305ac07511f097e325171f6cc4a20878d11ad771849
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/ca/38/16ba8d542e609997fdcd0214628421c971f8c395084085354b11ff4ac9c3/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/python/typing
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	PSFv2
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:           $(NO_TEST)
