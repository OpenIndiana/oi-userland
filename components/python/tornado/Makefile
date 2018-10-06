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
# Copyright (c) 2018 Till Wegmueller
#

include ../../../make-rules/shared-macros.mk

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		tornado
COMPONENT_VERSION=	4.5.3
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/tornado
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:6d14e47eab0e15799cf3cdcc86b0b98279da68522caace2bd7ce644287685f0a
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/source/t/tornado/$(COMPONENT_ARCHIVE)

PYTHON_VERSIONS=	2.7

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/setup.py.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_POST_INSTALL_ACTION= \
  gfind $(PROTO_DIR)$(PYTHON_VENDOR_PACKAGES.32) -type f \
    -exec gawk '/^\#!.*python/{print FILENAME}{nextfile}' {} + \
  | xargs gsed -i -e '1 s;^.*$$;\#!$(PYTHON.32);'

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:           $(NO_TEST)

REQUIRED_PACKAGES += library/python/backports.ssl_match_hostname-27
REQUIRED_PACKAGES += library/python/certifi-27
REQUIRED_PACKAGES += library/python/pycurl-27
REQUIRED_PACKAGES += library/python/python-mysql-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
