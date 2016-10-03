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

COMPONENT_NAME=		Elixir
COMPONENT_VERSION=	0.7.1
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Declarative Mapper for SQLAlchemy
COMPONENT_PROJECT_URL=	http://elixir.ematia.de/trac/wiki
COMPONENT_FMRI=		library/python/elixir
COMPONENT_CLASSIFICATION=Development/Python
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	https://pypi.python.org/packages/3d/8d/0009e2a623849894131f258529fe3a818c5734f7a9892f8721d99bd5cc31/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:a7ef437f25b544e4f74fb3236fc43cd25f5d6feb6037dd7c66931046d75439e9
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

PYTHON_VERSIONS= 2.7

build:          $(BUILD_NO_ARCH)

install:        $(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

REQUIRED_PACKAGES += runtime/python-27
