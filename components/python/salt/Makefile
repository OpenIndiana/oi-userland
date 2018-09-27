# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Till Wegmueller
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=salt
COMPONENT_VERSION=2018.3.2
COMPONENT_SUMMARY=	Portable, distributed, remote execution and configuration management system
COMPONENT_PROJECT_URL=http://saltstack.com
COMPONENT_FMRI=system/management/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=https://files.pythonhosted.org/packages/9b/84/48b46bad5fa13b47c10a71b4f58cf0f3a30fcb32b6a6599fca454b8c6256/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=sha256:d86eeea2e5387f4a64bbf0a11d103bfc8aac1122e19d39cc0945d33efdc797bd
COMPONENT_LICENSE=	Apache License 2.0
COMPONENT_LICENSE_FILE=LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

REQUIRED_PACKAGES+=library/python/futures-$(PYV)
REQUIRED_PACKAGES+=library/python/msgpack-python-$(PYV)
REQUIRED_PACKAGES+=library/python/pyyaml-$(PYV)
REQUIRED_PACKAGES+=library/python/jinja2-$(PYV)
REQUIRED_PACKAGES+=library/python/markupsafe-$(PYV)
REQUIRED_PACKAGES+=library/python/requests-$(PYV)
REQUIRED_PACKAGES+=library/python/tornado-$(PYV)
REQUIRED_PACKAGES+=runtime/python-$(PYV)
REQUIRED_PACKAGES+=library/python/pyzmq-$(PYV)
REQUIRED_PACKAGES+=library/python/cryptography-$(PYV)
