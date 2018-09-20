#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2017 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= 	pymongo
COMPONENT_VERSION= 	3.4.0
COMPONENT_REVISION=	1
COMPONENT_FMRI= 	library/python/$(COMPONENT_NAME)
COMPONENT_SRC= 		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= 	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
  sha256:d359349c6c9ff9f482805f89e66e476846317dc7b1eea979d7da9c0857ee2721
COMPONENT_ARCHIVE_URL= \
  https://pypi.python.org/packages/82/26/f45f95841de5164c48e2e03aff7f0702e22cef2336238d212d8f93e91ea8/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://api.mongodb.com/python/3.4.0/
COMPONENT_LICENSE_FILE=	LICENSE
COMPONENT_LICENSE=	Apache-2.0
COMPONENT_CLASSIFICATION= Development/Python

PYTHON_VERSIONS=	2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
