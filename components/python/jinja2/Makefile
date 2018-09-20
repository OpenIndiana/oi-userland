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
# Copyright 2015, PALO Richard.
# Copyright 2017 Gary Mills
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Jinja2
COMPONENT_VERSION=	2.8
COMPONENT_REVISION=	1
COMPONENT_CLASSIFICATION= Development/Python
COMPONENT_FMRI=		library/python/jinja2
COMPONENT_SUMMARY=	Fast and easy to use stand-alone template engine
COMPONENT_PROJECT_URL=	http://jinja.pocoo.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:bc1ff2ff88dbfacefde4ddde471d1417d3b304e8df103a7a9437d47269201bf4
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/J/Jinja2/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
