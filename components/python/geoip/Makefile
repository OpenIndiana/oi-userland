# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Adam Stevko
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		GeoIP
COMPONENT_VERSION=	1.3.2
COMPONENT_REVISION=	3
COMPONENT_PROJECT_URL=	http://www.maxmind.com/
COMPONENT_FMRI=		library/python/geoip
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/f2/7b/a463b7c3df8ef4b9c92906da29ddc9e464d4045f00c475ad31cdb9a97aae/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:a890da6a21574050692198f14b07aa4268a01371278dfc24f71cd9bc87ebf0e6
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE= LICENSE	

PYTHON_VERSIONS=2.7 3.4 3.5

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += database/geoip
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += runtime/python-34
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += system/library
