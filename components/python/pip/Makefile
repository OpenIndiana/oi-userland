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
# Copyright 2013 Adam Stevko. All rights reserved.
# Copyright 2019 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pip
COMPONENT_VERSION= 	19.0.3
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:afe5d018b19a8ef00996d6bc3629e6df401efd295c99b38cc4872e07568482ff
COMPONENT_ARCHIVE_URL=	https://github.com/pypa/pip/archive/$(COMPONENT_VERSION).tar.gz
COMPONENT_PROJECT_URL=	https://github.com/pypa/pip

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/setuptools-27
REQUIRED_PACKAGES += library/python/setuptools-34
REQUIRED_PACKAGES += library/python/setuptools-35
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
