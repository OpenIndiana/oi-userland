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

COMPONENT_NAME=		backports.functools_lru_cache
COMPONENT_VERSION=	1.5
COMPONENT_SUMMARY=	'Backport of functools.lru_cache from Python 3.3'
COMPONENT_PROJECT_URL=	https://pypi.org/project/backports.functools_lru_cache/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:9d98697f088eb1b0fa451391f91afb5e3ebde16bbdb272819fd091151fda4f1a
COMPONENT_ARCHIVE_URL=	$(call pypi_url)
COMPONENT_FMRI=	library/python/backports.functools_lru_cache
COMPONENT_CLASSIFICATION=	Development/Python
COMPONENT_LICENSE=	MIT
COMPONENT_LICENSE_FILE=	LICENSE

PYTHON_VERSIONS=	2.7

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/setup.py.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_ENV += SETUPTOOLS_SCM_PRETEND_VERSION=$(COMPONENT_VERSION)
COMPONENT_INSTALL_ENV += SETUPTOOLS_SCM_PRETEND_VERSION=$(COMPONENT_VERSION)

# common targets
build:		$(BUILD_NO_ARCH)

install:	$(INSTALL_NO_ARCH)

test:           $(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += library/python/setuptools_scm-27
