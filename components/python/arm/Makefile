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

COMPONENT_NAME=		arm
COMPONENT_VERSION=	1.4.5.0
COMPONENT_SUMMARY=	Terminal status monitor for Tor relays.
COMPONENT_PROJECT_URL=	https://www.torproject.org/projects/arm.html.en
COMPONENT_FMRI=		network/tor/arm
COMPONENT_CLASSIFICATION=System/Security
COMPONENT_SRC=          $(COMPONENT_NAME)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.bz2
COMPONENT_ARCHIVE_URL=	https://www.atagar.com/arm/resources/static/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:fc0e771585dde3803873b4807578060f0556cf1cac6c38840a714ffada3b28fa
COMPONENT_LICENSE=	GPLv3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

PYTHON_VERSIONS= 2.7

COMPONENT_INSTALL_ARGS = --root=$(PROTO_DIR)
COMPONENT_INSTALL_ARGS += --install-purelib=$(USRSHAREDIR)

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += library/python/elixir-27
REQUIRED_PACKAGES += library/python/geoip-27
REQUIRED_PACKAGES += library/python/sqlalchemy-27
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += SUNWcs
