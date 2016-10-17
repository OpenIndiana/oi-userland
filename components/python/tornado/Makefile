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

PATH=/usr/bin:/usr/gnu/bin:/usr/sbin

COMPONENT_NAME=		tornado
COMPONENT_VERSION=	4.1
COMPONENT_PROJECT_URL=	https://pypi.python.org/pypi/tornado
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:99abd3aede45c93739346ee7384e710120121c3744da155d5cff1c0101702228
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

REQUIRED_PACKAGES += library/python-2/pycurl-27
REQUIRED_PACKAGES += library/python-2/python-mysql-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += system/library
