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

COMPONENT_NAME=		more-itertools
COMPONENT_VERSION=	4.3.0
COMPONENT_SUMMARY=	'more-itertools - More routines for operating on iterables'
COMPONENT_PROJECT_URL=	https://pypi.org/project/more-itertools/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:c476b5d3a34e12d40130bc2f935028b5f636df8f372dc2c1c01dc19681b2039e
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/more-itertools
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:           $(NO_TEST)
